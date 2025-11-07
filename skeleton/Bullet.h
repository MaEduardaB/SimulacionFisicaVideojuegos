// Bullet.h
#pragma once
#include "Particle.h"

class Bullet : public Particle
{
public: 
    Bullet(Vector3 pos, Vector3 dir, double massReal, double velReal, double velSim);
    ~Bullet() = default;

private:
    double _massReal;
};
