#include "RigidBodySystem.h"
#include "RigidBodyGen.h"
#include "RenderUtils.hpp"

// variables globales de PhysX
extern physx::PxScene* gScene;
extern physx::PxPhysics* gPhysics;

RigidBodySystem::RigidBodySystem() : _rigidBodies(), _generators(), _materials() {
    
    //DIFERENTES TIPOS DE MATERIALES
    _materials.push_back(gPhysics->createMaterial(0.5f, 0.5f, 0.6f)); // Material estándar
    
    _materials.push_back(gPhysics->createMaterial(1.0f, 1.0f, 0.1f)); // Material PEGAJOSO
    _materials.push_back(gPhysics->createMaterial(0.1f, 0.1f, 0.9f)); // Material resbaladizo
}

RigidBodySystem::~RigidBodySystem() {
    for (auto rb : _rigidBodies) {
        if (rb) {
            gScene->removeActor(*rb);
            rb->release();
        }
    }
    _rigidBodies.clear();
    for (auto mat : _materials) {
        if (mat) mat->release();
    }
    _materials.clear();
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

void RigidBodySystem::createRigidBody(const RIGID_BODY_PROPS& props) {
    physx::PxMaterial* mat = _materials[props._materialType % _materials.size()];
    
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
        auto dyn = static_cast<physx::PxRigidDynamic*>(rb);
        dyn->setLinearVelocity(props._velocity);
        physx::PxRigidBodyExt::updateMassAndInertia(*dyn, static_cast<float>(props._mass));
        if (props._inertia.x != 0 || props._inertia.y != 0 || props._inertia.z != 0) {
            dyn->setMassSpaceInertiaTensor(physx::PxVec3(props._inertia.x, props._inertia.y, props._inertia.z));
        }
    } else {
        rb = gPhysics->createRigidStatic(physx::PxTransform(props._transform));
    }
    
    physx::PxShape* shape = gPhysics->createShape(*geo, *mat);
    rb->attachShape(*shape);
    addRigidBody(rb);
    
    delete geo;
}

void RigidBodySystem::addGenerator(RigidBodyGen* gen) {
    if (gen) _generators.push_back(gen);
}

void RigidBodySystem::createRigidBodies() {
    for (auto gen : _generators) {
        if (!gen) continue;
        auto propsList = gen->generateProps();
        for (const auto& props : propsList) {
            createRigidBody(props);
        }
    }
}

const std::list<physx::PxRigidActor*>& RigidBodySystem::getRigidBodies() const {
    return _rigidBodies;
}