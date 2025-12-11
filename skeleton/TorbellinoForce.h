#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
#include <PxPhysicsAPI.h>


class TorbellinoForce : public ForceGenerator
{
public:
    TorbellinoForce(const Vector3& center,
                    float radius,
                    float K,
                    float airDensity = 1.225f);

    void updateForce(physx::PxRigidDynamic* rb) override;
	Vector3 updateForce(Particle* p) override;

    Vector3 calculateForce(const Vector3& pos, const Vector3& vel, float mass) override;


    void setParameters(float K, float radius);
    void setArea(const Vector3& center, float radius);
protected:
    Vector3 _center;     // Centro del torbellino
    float _radius;       // Radio de acción
    float _K;            // Intensidad del torbellino
    float _air_density;  
};