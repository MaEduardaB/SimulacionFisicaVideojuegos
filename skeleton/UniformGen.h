#pragma once
#include "ParticleGen.h"
class UniformGen :
    public ParticleGen
{
public:

    UniformGen();
    UniformGen(std::mt19937 mt,
				Vector3 vel,
				Vector3 pos,
				double duration,
				double prob_Gen,
				int n_particles);


private:
    std::uniform_real_distribution<double> _u{ 0,1 };


};

