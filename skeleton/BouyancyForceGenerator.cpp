#include "BouyancyForceGenerator.h"
#include "Particle.h"
#include "RigidParticle.h"

BouyancyForceGenerator::BouyancyForceGenerator(float h, float v, float d, float posWater):
	_height(h), _volume(v), _liquid_density(d), _posWater(posWater)
{	
}


void BouyancyForceGenerator::updateForce(physx::PxRigidDynamic* rb) {
    if (!rb) return;
    physx::PxVec3 posPx = rb->getGlobalPose().p;
    physx::PxVec3 force = calculateForce(posPx, physx::PxVec3(0,0,0), rb->getMass());
    rb->addForce(force);
}

void BouyancyForceGenerator::updateForce(Particle* p)
{
    if (!p) return;
    p->addForce(calculateForce(p->getTransform().p, p->getVelocity(), p->getMass()));
}

void BouyancyForceGenerator::updateForce(RigidParticle* rp) {
    if (!rp || !rp->isDynamic()) return;
    physx::PxVec3 posPx = rp->getRigidBody()->getGlobalPose().p;
    physx::PxVec3 force = calculateForce(posPx, physx::PxVec3(0,0,0), rp->getMass());
    rp->addForce(force);
}

physx::PxVec3 BouyancyForceGenerator::calculateForce(const physx::PxVec3& pos, const physx::PxVec3& vel, float mass)
{
    float h = pos.y;
    float h0 = _posWater;

    float immersed = 0;
    if (h - h0 > _height * 0.5f) {
        immersed = 0.0f;
    } else if (h0 - h > _height * 0.5f) {
        immersed = 1.0f;
    } else {
        immersed = (h0 - h) / _height + 0.5f;
    }

    if (immersed < 0.0f) immersed = 0.0f;
    if (immersed > 1.0f) immersed = 1.0f;

    return physx::PxVec3(0, _liquid_density * _volume * immersed * 9.8f, 0);
}

