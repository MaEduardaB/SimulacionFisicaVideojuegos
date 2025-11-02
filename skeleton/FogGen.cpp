#include "FogGen.h"
#include "Constants.h"
#include "Particle.h"
#include "ParticleSystem.h" // Necesario para el callback

FogGen::FogGen()
    : ParticleGen(), _u(-0.5, 0.5)
{
}

FogGen::FogGen(std::mt19937 mt, Vector3 vel, Vector3 pos, double duration, double prob_Gen, int n_particles, float radius)
    : ParticleGen(mt, vel, pos, duration, prob_Gen, n_particles), _u(-0.5, 0.5), _radius(radius)
{
}

void FogGen::clearParticles()
{
}

std::list<Particle*> FogGen::generateP()
{
    std::list<Particle*> particles;
    std::uniform_real_distribution<double> prob(0.0, 1.0);
    if (prob(_mt) > _prob_Gen)
        return particles;
    
    double theta = 2.0 * 3.14159265 * prob(_mt);
    double phi   = acos(2.0 * prob(_mt) - 1.0);
    double r     = _radius * cbrt(prob(_mt));
    
    for (int i = 0; i < _n_particles; ++i)
    {

        Vector3 vel = Vector3(0.9f*_u(_mt), 0.05f*_u(_mt), 0.9f*_u(_mt));
        double r = _radius * cbrt(prob(_mt));
        
        // Pos aleatoria alrededor del emisor
        
        Vector3 pos = _pos + Vector3(_u(_mt), _u(_mt), _u(_mt)) * _radius;
        
        PARTICLES prop;
        prop._transform = pos;
        prop._velocity = vel;
        prop._aceleration = Vector3(0, 0, 0); // sin gravedad
        prop._mass = 0.1;
        prop._damping = 0.995;
        prop._type = INTEGRATETYPES::EULER_SEMI_IMPILICITO;
        prop._p_type = PARTICLE_TYPE::FOG;
        prop._lifeTime = 5.0 + 2.0*prob(_mt);
        prop._size = 0.5f + 0.1f * prob(_mt);

        Particle* p = new Particle(prop);
        p->setTime(_dur + 1.0 * prob(_mt));
        // Color gris transparente
        float alpha = 0.2f + 0.008f * prob(_mt);
        p->setColor(Vector4(0.8f, 0.8f, 0.8f, alpha));
        particles.push_back(p);
    }

    return particles;
}
