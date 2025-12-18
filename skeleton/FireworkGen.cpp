#include "FireworkGen.h"
#include "Constants.h"
#include "Particle.h"
#include "ForceRegestry.h"
#include "ParticleSystem.h" // Necesario para el callback

FireworkGen::FireworkGen()
    : ParticleGen(), _u(-1.0, 1.0)
{
}

FireworkGen::FireworkGen(std::mt19937 mt, Vector3 vel, Vector3 pos, double duration, double prob_Gen, int n_particles)
    : ParticleGen(mt, vel, pos, duration, prob_Gen, n_particles), _u(-1.0, 1.0)
{
    Vector3 launchPos = _pos;

    prop._transform = launchPos;
    prop._velocity = Vector3(0.0, 0.0, 0.0);
    prop._aceleration = Vector3(0.0, 0.0, 0.0);
    prop._mass = 10.0;
    prop._damping = 0.99;
    prop._type = INTEGRATETYPES::EULER_SEMI_IMPILICITO;
    prop._p_type = PARTICLE_TYPE::FIREWORK;
}


std::list<Particle*> FireworkGen::generateP()
{
    std::list<Particle*> particles;
    std::uniform_real_distribution<double> prob(-1.0, 1.0);

    if (prob(_mt) > _prob_Gen)
        return particles;

    Vector3 launchPos = _pos;
    Vector3 launchVel = _vel + Vector3(10 * prob(_mt), 30.0 + 10.0 * prob(_mt), 0.0);

    prop._velocity = launchVel;
 
    Particle* rocket = new Particle(prop);
    rocket->setTime(_dur + 1.0 * prob(_mt));
    
    rocket->setOnDeath([this](ParticleSystem& system, const Particle& p) {
        std::uniform_real_distribution<double> rand(-1.0, 1.0);
        std::uniform_real_distribution<double> t(0.8, 1.5);

        for (int i = 0; i < _n_particles; ++i)
        {
            Vector3 sparkVel(
                5.0 * rand(_mt),
                5.0 * rand(_mt),
                5.0 * rand(_mt)
            );

            PARTICLES sprop;
            sprop._transform = p.getTransform().p; 
            sprop._velocity = sparkVel;
            sprop._aceleration = Vector3(0.0, 0.0, 0.0);
            sprop._mass = 0.2;
            sprop._damping = 0.98;
            sprop._p_type = PARTICLE_TYPE::SPARK;
            sprop._type = INTEGRATETYPES::EULER_SEMI_IMPILICITO;

            Particle* spark = new Particle(sprop);
            spark->setTime(t(_mt));

            system.addParticle(spark);
        }
    });

    particles.push_back(rocket);
    return particles;
}
