#pragma once
#include "ForceGenerator.h"
class BouyancyForceGenerator :
    public ForceGenerator
{
public:
    BouyancyForceGenerator(float h, float v, float d, float posWater);
    ~BouyancyForceGenerator() = default;
    
    Vector3 updateForce(Particle* p) override;
    void updateForce(physx::PxRigidDynamic* rb) override;

    Vector3 calculateForce(const Vector3& pos, const Vector3& vel, float mass) override;

protected:
    float _height;
    float _volume;
    float _liquid_density;
    float _posWater;
};

