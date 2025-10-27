#include "GaussianGen.h"
#include "Constants.h"
#include "Particle.h"
#include <list>

GaussianGen::GaussianGen()
    : ParticleGen(), _u(0.0, 1.0)
{
}

GaussianGen::GaussianGen(std::mt19937 mt, Vector3 vel, Vector3 pos, double duration, double prob_Gen, int n_particles)
    : ParticleGen(mt, vel, pos, duration, prob_Gen, n_particles), _u(0.0, 1.0)
{
}


void GaussianGen::clearParticles()
{
}

std::list<Particle*> GaussianGen::generateP()
{
    std::list<Particle*> particles;
    std::uniform_real_distribution<double> prob(0.0, 1.0);
    
    if (prob(_mt) > _prob_Gen)
        return particles;

    //int numParticles = std::distCount(_mt);
    int numParticles = 0;

    for (int i = 0; i < _n_particles; ++i)
    {
        /*_vel = vel + _u(_mt);
        _pos = pos + _u(_mt);*/
        
         Vector3 pos = Vector3(
            _pos.x + 0.2 * _u(_mt),
            _pos.y + 0.2 * _u(_mt),
            _pos.z + 0.2 * _u(_mt)
        );

        Vector3 vel = Vector3(
            _vel.x + _u(_mt),
            _vel.y + _u(_mt),
            _vel.z + _u(_mt)
        );

        _dur = _dur + _u(_mt);

        // duracion = duracion + _u(_mt);
        //Particle* p = new Particle(pos, vel, acc, INTEGRATETYPES::EULER_SEMI_IMPILICITO);
        //p->setTime(_duration);
        PARTICLES prop;
        prop._transform = pos;
        prop._velocity = vel;
        prop._aceleration = Vector3(0.0, -10.0, 0.0); // gravedad
        prop._mass = 1.0;
        prop._damping = 0.99;
        prop._type = INTEGRATETYPES::EULER_SEMI_IMPILICITO;

        Particle* p = new Particle(prop);
        p->setTime(_dur + 0.5 * std::abs(_u(_mt)));
        particles.push_back(p);
    }
    
    return particles;
}
