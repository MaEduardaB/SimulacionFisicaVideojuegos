#pragma once
#include <random>

#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "ForceGenerator.h"

#include<list>

class Particle;

class GravityForce : public ForceGenerator
{
public:
	GravityForce();
	void updateForce(Particle* p) override;
	Vector3 calculateForce(Particle* p) override;
protected:
	float _gravity = -9.8f;
};

