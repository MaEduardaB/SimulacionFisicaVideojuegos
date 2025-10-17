#include "GaussianGen.h"
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


std::list<Particle*> GaussianGen::generateP()
{
    std::list<Particle*> particles;
    std::uniform_real_distribution<double> prob(0.0, 1.0);

    int numParticles = std::distCount(_mt);

    for (int i = 0; i < _n_particles; ++i)
    {
        /*_vel = vel + _u(_mt);
        _pos = pos + _u(_mt);*/
        
        _pos = Vector3(_pos.x + _u(_mt), _pos.y + _u(_mt), _pos.z + _u(_mt));
        _vel = Vector3(_vel.x + _u(_mt), _vel.y + _u(_mt), _vel.z + _u(_mt));
        _dur = _dur + _u(_mt);

        // duracion = duracion + _u(_mt);
        //Particle* p = new Particle(pos, vel, acc, INTEGRATETYPES::EULER_SEMI_IMPILICITO);
        //p->setTime(_duration);
 
        //particles.push_back(p);
    }

    _n_particles = numParticles;
    return particles;
}
