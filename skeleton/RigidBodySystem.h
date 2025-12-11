#pragma once
#include <list>
#include <vector>
#include <PxPhysicsAPI.h>
#include "Constants.h"

class RigidBodyGen;

class RigidBodySystem {
public:
    RigidBodySystem();
    ~RigidBodySystem();
    void addRigidBody(physx::PxRigidActor* rb);
    void createRigidBody(const RIGID_BODY_PROPS& props);
    void addGenerator(RigidBodyGen* gen);
    void createRigidBodies();
    const std::list<physx::PxRigidActor*>& getRigidBodies() const;

    
private:
    std::list<physx::PxRigidActor*> _rigidBodies;
    std::list<RigidBodyGen*> _generators;
    std::vector<physx::PxMaterial*> _materials;
};