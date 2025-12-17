#pragma once
#include "ParticleGen.h"
class FogGen :
    public ParticleGen
{
public:

    FogGen();
    FogGen(std::mt19937 mt,
				Vector3 vel,
				Vector3 pos,
				double duration,
				double prob_Gen,
				int n_particles, 
				float radius);

	std::list<Particle*> generateP() override;

private:
    std::uniform_real_distribution<double> _u{ 0,1 };

	float _radius = 1.0f;
};

