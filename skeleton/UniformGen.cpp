
#include "UniformGen.h"

UniformGen::UniformGen()
	: ParticleGen(), _u(0.0, 1.0)
{
}

UniformGen::UniformGen(std::mt19937 mt, Vector3 vel, Vector3 pos, double duration, double prob_Gen, int n_particles)
	: ParticleGen(mt, vel, pos, duration, prob_Gen, n_particles), _u(0.0, 1.0)
{
}
