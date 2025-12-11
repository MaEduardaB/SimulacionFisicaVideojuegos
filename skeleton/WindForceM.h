#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class WindForceM : public ForceGenerator
{
public:
    WindForceM(const Vector3& windVelocity,
                const Vector3& areaCenter,
                const Vector3& areaHalfSize,
                float airDensity = 1.225f);

    Vector3 updateForce(Particle* p) override;
    void updateForce(physx::PxRigidDynamic* rb) override;

    Vector3 calculateForce(const Vector3& pos, const Vector3& vel, float mass) override;

    void setObjectProperties(float area, float dragCoeff, const Vector3& normal);

protected:
    Vector3 _windVelocity;
    Vector3 _areaCenter;
    Vector3 _areaHalfSize;
    float _air_density;     // ρ
    float _objectArea;     // A
    float _dragCoeff;      // C_D
    Vector3 _normal;       // normal del objeto
};
