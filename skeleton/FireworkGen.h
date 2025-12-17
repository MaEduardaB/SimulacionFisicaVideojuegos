#pragma once
#include "ParticleGen.h"
#include "Constants.h"
class FireworkGen :
    public ParticleGen
{
public:

    FireworkGen();
    FireworkGen(std::mt19937 mt,
				Vector3 vel,
				Vector3 pos,
				double duration,
				double prob_Gen,
				int n_particles);

	std::list<Particle*> generateP() override;

private:
    std::uniform_real_distribution<double> _u{ -1,1 };

	PARTICLES prop;
};

