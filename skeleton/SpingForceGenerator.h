#pragma once
#include "ForceGenerator.h"
class SpingForceGenerator :
    public ForceGenerator
{
public:
    SpingForceGenerator(Particle* other, double k, double resting_length);
    ~SpingForceGenerator() = default;
    
    void updateForce(Particle* p) override;
    Vector3 calculateForce(Particle* p) override;
    inline void setK(double k) { _k = k; };

protected:
    double _k;
    double _resting_length;
    Particle* _other;
};

