#pragma once
#include "ParticleGen.h"
class RainGen :
    public ParticleGen
{
public:

    RainGen();
    RainGen(std::mt19937 mt,
				Vector3 vel,
				Vector3 pos,
				double duration,
				double prob_Gen,
				int n_particles);

	std::list<Particle*> generateP() override;

private:
    std::uniform_real_distribution<double> _u{ 0,1 };
};

