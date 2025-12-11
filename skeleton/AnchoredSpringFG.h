#pragma once
#include "SpringForceGenerator.h"

class AnchoredSpringFG :
    public SpringForceGenerator
{
public:
    AnchoredSpringFG(double k, double resting_length, const Vector3& _anchorPos);
    ~AnchoredSpringFG();
    
    Vector3 updateForce(Particle* p) override;
    void updateForce(physx::PxRigidDynamic* rb) override;

    Vector3 calculateForce(const Vector3& pos, const Vector3& vel, float mass) override;
    inline void setK(double k) { _k = k; };
};

