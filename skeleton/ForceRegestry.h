#pragma once
#include <random>

#include <PxPhysicsAPI.h>
#include "core.hpp"

#include<list>

class Particle;
class ForceGenerator;

class ForceRegestry
{
public:
	ForceRegestry();
	void add(Particle* p, ForceGenerator* fg);
	// remove, clear, update
	void remove(Particle* p, ForceGenerator* fg);
	void clear();
	void updateForces();

	void removeForce(ForceGenerator* fg);

	void removeInvalid(const std::list<std::unique_ptr<Particle>>& particles);
protected:
	std::list<std::pair<Particle*, ForceGenerator*>> _registry;
};

