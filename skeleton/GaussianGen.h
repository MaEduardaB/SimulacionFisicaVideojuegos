#pragma once
#include "ParticleGen.h"
class GaussianGen :
    public ParticleGen
{
public:

	GaussianGen();
	GaussianGen(std::mt19937 mt,
		Vector3 vel,
		Vector3 pos,
		double duration,
		double prob_Gen,
		int n_particles);

	std::list<Particle*> generateP() override;

private:
	std::normal_distribution<double> _u{ 0,1 };
};

