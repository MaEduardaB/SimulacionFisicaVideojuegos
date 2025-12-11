#include "RigidBodySystem.h"
#include "RenderUtils.hpp"
#include "Constants.h"

// variables globales de PhysX (definidas en main.cpp)
extern physx::PxScene* gScene;
extern physx::PxPhysics* gPhysics;
extern physx::PxMaterial* gMaterial; 

RigidBodySystem::RigidBodySystem() : _rigidBodies() {}

RigidBodySystem::~RigidBodySystem() {
    for (auto rb : _rigidBodies) {
        if (rb) {
            gScene->removeActor(*rb);
            rb->release();
        }
    }
    _rigidBodies.clear();
}

void RigidBodySystem::addRigidBody(physx::PxRigidActor* rb) {
    if (rb) {
        _rigidBodies.push_back(rb);
        gScene->addActor(*rb);
        physx::PxShape* shape = nullptr;
        rb->getShapes(&shape, 1);
        if (shape) {
            new RenderItem(shape, rb, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
        }
    }
}

void RigidBodySystem::createRigidBody(const RIGID_BODY_PROPS& props, physx::PxMaterial* mat) {
    if (!mat) mat = gMaterial; 
    
    physx::PxGeometry* geo = nullptr;
    if (props._shapeType == "SPHERE") {
        geo = new physx::PxSphereGeometry(props._sizeX);
    } else if (props._shapeType == "BOX") {
        geo = new physx::PxBoxGeometry(props._sizeX, props._sizeY, props._sizeZ);
    } else {
        geo = new physx::PxSphereGeometry(props._sizeX);
    }
    
    physx::PxRigidActor* rb;
    if (props._isDynamic) {
        rb = gPhysics->createRigidDynamic(physx::PxTransform(props._transform));
        static_cast<physx::PxRigidDynamic*>(rb)->setLinearVelocity(props._velocity);
        physx::PxRigidBodyExt::updateMassAndInertia(*static_cast<physx::PxRigidDynamic*>(rb), static_cast<float>(props._mass));
    } else {
        rb = gPhysics->createRigidStatic(physx::PxTransform(props._transform));
    }
    
    physx::PxShape* shape = gPhysics->createShape(*geo, *mat);
    rb->attachShape(*shape);
    addRigidBody(rb);
    
    delete geo;
}



const std::list<physx::PxRigidDynamic*>& RigidBodySystem::getRigidBodies() const {
    return _rigidBodies;
}