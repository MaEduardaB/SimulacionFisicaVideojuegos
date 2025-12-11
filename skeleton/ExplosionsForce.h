#pragma once
#include "ForceGenerator.h"
class ExplosionsForce :
    public ForceGenerator
{
public:
    ExplosionsForce(const Vector3 & center, float K, float radius, float tau, float expansionVel = 0.0f);

    Vector3 updateForce(Particle* p) override;
    void updateForce(physx::PxRigidDynamic* rb) override;

    Vector3 calculateForce(const Vector3& pos, const Vector3& vel, float mass) override;
    void updateTime(float dt);
    bool hasFaded() const;
    bool isInsideArea(const Vector3 & pos) const;

protected:
    Vector3 _center;
    float _K;
    float _R;
    float _decaimento;
    float _expVel;
    float _time;
};
