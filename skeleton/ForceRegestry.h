#pragma once
#include <random>

#include <PxPhysicsAPI.h>
#include "core.hpp"

#include<list>

class Particle;
class RigidParticle;
class ForceGenerator;

class ForceRegestry
{
public:
	ForceRegestry();
	void add(Particle* p, ForceGenerator* fg);
	void add(RigidParticle* p, ForceGenerator* fg);
	void add(physx::PxRigidActor* p, ForceGenerator* fg);
	// remove, clear, update
	void remove(Particle* p, ForceGenerator* fg);
	void remove(RigidParticle* p, ForceGenerator* fg);
	void remove(physx::PxRigidActor* p, ForceGenerator* fg);
	void clear();
	void updateForces();

	void removeForce(ForceGenerator* fg);

	void removeInvalid(const std::list<std::unique_ptr<Particle>>& particles);
	
	void removeInvalid(const std::list<RigidParticle*>& particles);
	
	void removeInvalid(const std::list<std::unique_ptr<physx::PxRigidActor>>& particles);
protected:
	std::list<std::pair<Particle*, ForceGenerator*>> _registryParticles;
	std::list<std::pair<RigidParticle*, ForceGenerator*>> _registryRigidParticles;
	std::list<std::pair<physx::PxRigidActor*, ForceGenerator*>> _registryRigids;
};

