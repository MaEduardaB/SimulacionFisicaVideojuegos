#pragma once
#include "ForceGenerator.h"
class SpringForceGenerator :
    public ForceGenerator
{
public:
    SpringForceGenerator(Particle* other, double k, double resting_length);
    ~SpringForceGenerator() = default;
    
    Vector3 updateForce(Particle* p) override;
    void updateForce(physx::PxRigidDynamic* rb) override;

    Vector3 calculateForce(const Vector3& pos, const Vector3& vel, float mass) override;
    inline void setK(double k) { _k = k; };

protected:
    double _k;
    double _resting_length;
    Particle* _other;
};

