#pragma once
#include "Particle.h"
class Bullet :
    public Particle
{
public: 
    Bullet(Vector3 pos, Vector3 vel, Vector3 ace, double mass);
    ~Bullet();

private:

    double _mass;
};

