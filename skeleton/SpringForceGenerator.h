#pragma once
#include "ForceGenerator.h"
class SpringForceGenerator :
    public ForceGenerator
{
public:
    SpringForceGenerator(Particle* other, double k, double resting_length);
    SpringForceGenerator(RigidParticle* other, double k, double resting_length);
    ~SpringForceGenerator() = default;
    
    void updateForce(physx::PxRigidDynamic* rb) override;
	void updateForce(Particle* p) override;
    void updateForce(RigidParticle* rp) override;

    Vector3 calculateForce(const Vector3& pos, const Vector3& vel, float mass) override;
    inline void setK(double k) { _k = k; };

protected:
    double _k;
    double _resting_length;
    bool _isRigid;
    union {
        Particle* _otherParticle;
        RigidParticle* _otherRigid;
    };
};

