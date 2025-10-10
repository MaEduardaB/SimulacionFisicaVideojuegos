#include "GaussianGen.h"


GaussianGen::GaussianGen()
    : ParticleGen(), _u(0.0, 1.0)
{
}

GaussianGen::GaussianGen(std::mt19937 mt, Vector3 vel, Vector3 pos, double duration, double prob_Gen, int n_particles)
    : ParticleGen(mt, vel, pos, duration, prob_Gen, n_particles), _u(0.0, 1.0)
{
}

ParticleGen::ParticleGen()
{
}

std::list<Particle*> GaussianGen::generateP()
{
    return std::list<Particle*>();
}
