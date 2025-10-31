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
	virtual Vector3 calculateForce(Particle* p) = 0;
protected:
	Vector3 _force;
};

