#include "RigidBodySystem.h"
#include "RigidBodyGen.h"
#include "RigidParticle.h"
#include "ForceRegestry.h"
#include "RenderUtils.hpp"
#include "GravityForce.h"
#include "core.hpp" 

using namespace physx;

RigidBodySystem::RigidBodySystem() : _rigidBodies(), _generators(), _materials(), _force_registry(new ForceRegestry()) {
    
    //DIFERENTES TIPOS DE MATERIALES
    if (gPhysics) {
        _materials.push_back(gPhysics->createMaterial(0.5f, 0.5f, 0.6f)); // Material estándar
        
        _materials.push_back(gPhysics->createMaterial(1.0f, 1.0f, 0.1f)); // Material PEGAJOSO
        _materials.push_back(gPhysics->createMaterial(0.1f, 0.1f, 0.9f)); // Material resbaladizo
    }

    _gravityForce = new GravityForce();
}

RigidBodySystem::~RigidBodySystem() {
    delete _gravityForce;
    delete _force_registry;

    for (auto rp : _rigidBodies) {
        delete rp;
    }
    _rigidBodies.clear();

    for (auto mat : _materials)
        mat->release();
    _materials.clear();
}

void RigidBodySystem::update(double t)
{
    _force_registry->updateForces();

    for (auto it = _rigidBodies.begin(); it != _rigidBodies.end(); ) {
        RigidParticle* rp = *it;
        if (!rp) {
            it = _rigidBodies.erase(it);
            continue;
        }
        
        if (rp->isDynamic()) {
            rp->integrate(t);
            if (!rp->isAlive()) {
                delete rp;
                it = _rigidBodies.erase(it);
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }

    _force_registry->removeInvalid(_rigidBodies);
}

void RigidBodySystem::registerGravity(RigidParticle* rp)
{
    if (!_gravityForce || !rp->isDynamic()) return;

    auto dyn = static_cast<PxRigidDynamic*>(rp->getRigidBody());
    dyn->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
    _force_registry->add(dyn, _gravityForce);
}

void RigidBodySystem::addRigidBody(RigidParticle* rp) {
    if (rp) {
        _rigidBodies.push_back(rp);
        registerGravity(rp);
    }
}

void RigidBodySystem::createRigidBody(const RIGID_BODY_PROPS& props) {
    physx::PxMaterial* mat = _materials.empty() ? gMaterial : _materials[props._materialType % _materials.size()];
    RigidParticle* rp = new RigidParticle(props, mat);
    addRigidBody(rp);
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

const std::list<RigidParticle*>& RigidBodySystem::getRigidBodies() const {
    return _rigidBodies;
}