#pragma once
#include <list>
#include <vector>
#include <PxPhysicsAPI.h>
#include "Constants.h"

class RigidBodyGen;
class ForceRegestry;
class GravityForce;

class RigidBodySystem {
public:
    RigidBodySystem();
    ~RigidBodySystem();
    void update(double t);

    void addRigidBody(physx::PxRigidActor* rb);
    void createRigidBody(const RIGID_BODY_PROPS& props);
    void addGenerator(RigidBodyGen* gen);
    void createRigidBodies();
    const std::list<physx::PxRigidActor*>& getRigidBodies() const;

    void registerGravity(physx::PxRigidActor* rb);
    
private:
    std::list<physx::PxRigidActor*> _rigidBodies;
    std::list<RigidBodyGen*> _generators;

    std::vector<physx::PxMaterial*> _materials;

    ForceRegestry* _force_registry;
    GravityForce*  _gravityForce;
};