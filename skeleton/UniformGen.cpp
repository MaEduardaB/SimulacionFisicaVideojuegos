
#include "UniformGen.h"
#include "Constants.h"
#include "Particle.h"

UniformGen::UniformGen()
	: ParticleGen(), _u(0.0, 1.0)
{
}

UniformGen::UniformGen(std::mt19937 mt, Vector3 vel, Vector3 pos, double duration, double prob_Gen, int n_particles)
	: ParticleGen(mt, vel, pos, duration, prob_Gen, n_particles), _u(0.0, 1.0)
{
}


void UniformGen::clearParticles()
{
}

std::list<Particle*> UniformGen::generateP()
{
    std::list<Particle*> particles;
    std::uniform_real_distribution<double> prob(0.0, 1.0);

    // Probabilidad de emisión
    if (prob(_mt) > _prob_Gen)
        return particles;

    for (int i = 0; i < _n_particles; ++i)
    {
        // Variación uniforme en posición y velocidad
        Vector3 pos = Vector3(
            _pos.x + _u(_mt),
            _pos.y + _u(_mt),
            _pos.z + _u(_mt)
        );

        Vector3 vel = Vector3(
            _vel.x + _u(_mt),
            _vel.y + _u(_mt),
            _vel.z + _u(_mt)
        );

        PARTICLES prop;
        prop._transform = pos;
        prop._velocity = vel;
        prop._aceleration = Vector3(0.0, -10.0, 0.0); // gravedad
        prop._mass = 1.0;
        prop._damping = 0.99;
        prop._type = INTEGRATETYPES::EULER_SEMI_IMPILICITO;

        Particle* p = new Particle(prop);
        p->setTime(_dur + 0.5 * _u(_mt)); // duración con ligera variación

        particles.push_back(p);
    }

    return particles;
}