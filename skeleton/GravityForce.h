#pragma once
#include <random>

#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "ForceGenerator.h"

class Particle;

class GravityForce : public ForceGenerator
{
public:
	GravityForce();
	void updateForce(physx::PxRigidDynamic* rb) override;
	void updateForce(RigidParticle* rp) override;
	void updateForce(Particle* p) override;

	physx::PxVec3 calculateForce(const physx::PxVec3& pos, const physx::PxVec3& vel, float mass) override;
protected:
	float _gravity = -9.8f;
};

