#include "RainGen.h"
#include "Constants.h"
#include "Particle.h"
#include "ParticleSystem.h" // Necesario para el callback

RainGen::RainGen()
    : ParticleGen(), _u(-1.0, 1.0)
{
}

RainGen::RainGen(std::mt19937 mt, Vector3 vel, Vector3 pos, double duration, double prob_Gen, int n_particles)
    : ParticleGen(mt, vel, pos, duration, prob_Gen, n_particles), _u(-1.0, 1.0)
{
}

void RainGen::clearParticles()
{
}

std::list<Particle*> RainGen::generateP()
{
    std::list<Particle*> particles;
    std::uniform_real_distribution<double> prob(-1.0, 1.0);

    if (prob(_mt) > _prob_Gen)
        return particles;

    int n_drops = _n_particles;
    for (int i = 0; i < n_drops; ++i)
    {
        Vector3 launchPos = Vector3(_u(_mt)*10.0f, 40.0f, _u(_mt)*15.0f);

        PARTICLES prop;
        prop._transform = launchPos;
        prop._velocity = Vector3(0.0f, 0.0f, 0.0f);
        prop._aceleration = Vector3(0.0f, 0.0f, 0.0f);
        prop._mass = 10.0f;
        prop._damping = 0.99;
        prop._type = INTEGRATETYPES::EULER_SEMI_IMPILICITO;
        prop._p_type = PARTICLE_TYPE::RAIN;

        Particle* drop = new Particle(prop);
        drop->setTime(_dur + 1.0 * prob(_mt));

        // Callback al morir para “explotar” gotas
        drop->setOnDeath([this](ParticleSystem& system, const Particle& p) {
            std::uniform_real_distribution<float> randXY(-1.0f, 1.0f);
            std::uniform_real_distribution<float> velY(1.0f, 2.0f);
            std::uniform_real_distribution<float> life(0.5f, 1.5f);

            for (int j = 0; j < _n_particles; ++j)
            {
                Vector3 sparkVel(
                    2.0f * randXY(_mt),
                    velY(_mt),
                    2.0f * randXY(_mt)
                );

                PARTICLES sprop;
                sprop._transform = p.getTransform().p;
                sprop._velocity = sparkVel;
                sprop._aceleration = Vector3(0.0f, 0.0f, 0.0f);
                sprop._mass = 10.0f;
                sprop._damping = 0.98f;
                sprop._p_type = PARTICLE_TYPE::NORMAL;
                sprop._type = INTEGRATETYPES::EULER_SEMI_IMPILICITO;
                sprop._size = 0.5f;

                Particle* spark = new Particle(sprop);
                spark->setTime(life(_mt));
                system.addParticle(spark);
            }
        });

        particles.push_back(drop);
    }

    return particles;
}
