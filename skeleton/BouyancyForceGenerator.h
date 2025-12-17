#pragma once
#include "ForceGenerator.h"
class BouyancyForceGenerator :
    public ForceGenerator
{
public:
    BouyancyForceGenerator(float h, float v, float d, float posWater);
    ~BouyancyForceGenerator() = default;
    
    void updateForce(Particle* p) override;
    void updateForce(physx::PxRigidDynamic* rb) override;

    physx::PxVec3 calculateForce(const physx::PxVec3& pos, const physx::PxVec3& vel, float mass) override;

protected:
    float _height;
    float _volume;
    float _liquid_density;
    float _posWater;
};

