#pragma once
#include <random>

#include <PxPhysicsAPI.h>
#include "core.hpp"

#include<list>
class Particle;
class ForceGenerator
{
public:
	ForceGenerator() = default;
	virtual void updateForce(Particle* p) = 0;
	virtual void updateForce(physx::PxRigidDynamic* rb) = 0;
	virtual physx::PxVec3 calculateForce(const physx::PxVec3& pos, const physx::PxVec3& vel, float mass) = 0;

protected:
	Vector3 _force;
};

