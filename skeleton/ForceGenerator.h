#pragma once
#include <random>

#include <PxPhysicsAPI.h>
#include "core.hpp"

#include<list>

class ForceGenerator
{
public:
	ForceGenerator() = default;
	virtual Vector3 updateForce(Particle* p) = 0;
	virtual void updateForce(physx::PxRigidDynamic* rb) = 0;
	virtual Vector3 calculateForce(const Vector3& pos, const Vector3& vel, float mass) = 0;

protected:
	Vector3 _force;
};

