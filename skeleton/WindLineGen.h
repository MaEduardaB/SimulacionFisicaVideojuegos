#pragma once
#include "ParticleGen.h"

class WindLineGen : public ParticleGen
{
public:
    WindLineGen();
    WindLineGen(std::mt19937 mt,
               Vector3 start,
               Vector3 end,
               Vector3 windVelocity,
               double prob_Gen,
               int n_particles);

    std::list<Particle*> generateP() override;

private:
    Vector3 _start;
    Vector3 _end;
    std::uniform_real_distribution<double> _u{ 0, 1 };
};