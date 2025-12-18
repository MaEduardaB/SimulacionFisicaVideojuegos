#pragma once
#include <list>
#include <vector>
#include <PxPhysicsAPI.h>
#include "Constants.h"

class RigidBodyGen;
class RigidParticle;
class ForceRegestry;
class GravityForce;

class RigidBodySystem {
public:
    RigidBodySystem();
    ~RigidBodySystem();
    void update(double t);

    void addRigidBody(RigidParticle* rp);
    void createRigidBody(const RIGID_BODY_PROPS& props);
    void addGenerator(RigidBodyGen* gen);
    void createRigidBodies();
    const std::list<RigidParticle*>& getRigidBodies() const;

    void registerGravity(RigidParticle* rp);
    
private:
    std::list<RigidParticle*> _rigidBodies;
    std::list<RigidBodyGen*> _generators;

    std::vector<physx::PxMaterial*> _materials;

    ForceRegestry* _force_registry;
    GravityForce*  _gravityForce;
};