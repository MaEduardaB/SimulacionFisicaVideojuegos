#include "ParticleGen.h"
#include "ParticleGen.h"

ParticleGen::ParticleGen()
	: _mt(), _vel(), _pos(), _duration(0.0), _prob_Gen(0.0), _n_particles_min(1), _n_particles_max(10)
{
}

ParticleGen::ParticleGen(std::mt19937 mt,
						 Vector3 vel,
						 Vector3 pos,
						 double duration,
						 double prob_Gen,
						 int n_particles_min,
						 int n_particles_max)
	: _mt(mt), _vel(vel), _pos(pos), _duration(duration), _prob_Gen(prob_Gen), _n_particles_min(n_particles_min), _n_particles_max(n_particles_max)
{
}

std::list<Particle *> ParticleGen::generateP()
{

    // para n particulas, prob Gen
    // pos = pos + _d(_mt)*distPos
    // vel = vel + _d(_mt)*distVel
    // dur = dur + _d(_mt)*distdur
    // clona PModel y asigna pos, vel, dur

    
    return std::list<Particle *>();
}
