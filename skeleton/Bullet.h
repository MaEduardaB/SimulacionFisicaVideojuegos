#pragma once
#include "Particle.h"
class Bullet :
    public Particle
{
public: 
    Bullet(Vector3 pos, Vector3 dir, double massReal, double velReal, double velSim, Vector3 gravedad);
    ~Bullet();

    void integrate(double t) override;
private:

    double _mass;

    double _massReal;
};

