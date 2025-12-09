#pragma once
#include "ForceGenerator.h"
class BouyancyForceGenerator :
    public ForceGenerator
{
public:
    BouyancyForceGenerator(float h, float v, float d, float posWater);
    ~BouyancyForceGenerator() = default;
    
    void updateForce(Particle* p) override;
    Vector3 calculateForce(Particle* p) override;

protected:
    float _height;
    float _volume;
    float _liquid_density;
    float _posWater;
};

