#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
#include <PxPhysicsAPI.h>


class WindForce : public ForceGenerator
{
public:
     WindForce(const Vector3& windVelocity,
              const Vector3& areaCenter,
              const Vector3& areaHalfSize,
              float k1 = 1.0f,
              float k2 = 0.0f);

    void updateForce(Particle* p) override;
    void updateForce(physx::PxRigidDynamic* rb) override;

    physx::PxVec3 calculateForce(const physx::PxVec3& pos, const physx::PxVec3& vel, float mass) override;

    bool isInsideArea(const Vector3& pos) const;

    bool isActive() const { return _active; }
    void setActive(bool active) { _active = active; }
protected:
    Vector3 _windVelocity;
    Vector3 _areaCenter;     // centro
    Vector3 _areaHalfSize;   // tamaño 
    float _k1, _k2;

private:
    bool _active;
};