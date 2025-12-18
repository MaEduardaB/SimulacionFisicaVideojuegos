#include "GravityForce.h"
#include "Constants.h"
#include "Particle.h"
#include "RigidParticle.h"

GravityForce::GravityForce(){
    _force = Vector3(0.0f, _gravity, 0.0f);
}

void GravityForce::updateForce(physx::PxRigidDynamic *rb)
{
    if (!rb) return;
    physx::PxVec3 posPx = rb->getGlobalPose().p;
    physx::PxVec3 velPx = rb->getLinearVelocity();
    physx::PxVec3 force = calculateForce(posPx, velPx, rb->getMass());
    rb->addForce(force);
}

void GravityForce::updateForce(Particle *p)
{      
    if(p)
        p->addForce(calculateForce(p->getTransform().p, p->getVelocity(), p->getMass()));   
}

physx::PxVec3 GravityForce::calculateForce(const physx::PxVec3& pos, const physx::PxVec3& vel, float mass)
{
    return physx::PxVec3(0.0f, _gravity * mass, 0.0f);
}

void GravityForce::updateForce(RigidParticle* rp) {
    if (!rp || !rp->isDynamic()) return;
    physx::PxVec3 posPx = rp->getRigidBody()->getGlobalPose().p;
    physx::PxVec3 velPx = static_cast<physx::PxRigidDynamic*>(rp->getRigidBody())->getLinearVelocity();
    physx::PxVec3 force = calculateForce(posPx, velPx, rp->getMass());
    rp->addForce(force);
}
