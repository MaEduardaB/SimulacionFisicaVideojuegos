// WindForceM.cpp
#include "WindForceM.h"
#include "Particle.h"
#include "RigidParticle.h"
#include <iostream>
#include <cmath>

WindForceM::WindForceM(const Vector3& windVelocity,
    const Vector3& areaCenter,
    const Vector3& areaHalfSize,
    float airDensity)
    : _windVelocity(windVelocity),
    _areaCenter(areaCenter),
    _areaHalfSize(areaHalfSize),
    _air_density(airDensity),
    _objectArea(1.0f),
    _dragCoeff(0.5f),
    _normal(windVelocity.magnitude() > 1e-6f ? windVelocity.getNormalized() : Vector3(0.0f, 0.0f, 1.0f))
{
}

void WindForceM::setObjectProperties(float area, float dragCoeff, const Vector3& normal)
{
    _objectArea = area;
    _dragCoeff = dragCoeff;
    if (normal.magnitude() > 1e-6f)
        _normal = normal.getNormalized();
}

void WindForceM::updateForce(Particle* p)
{
    if (!p) return;

    Vector3 pos = p->getTransform().p;

    Vector3 f = calculateForce(pos, p->getVelocity(), p->getMass());
    p->addForce(f);
}

void WindForceM::updateForce(physx::PxRigidDynamic* rb) {
    if (!rb) return;
    physx::PxVec3 posPx = rb->getGlobalPose().p;
    physx::PxVec3 velPx = rb->getLinearVelocity();
    physx::PxVec3 force = calculateForce(posPx, velPx, rb->getMass());
    rb->addForce(force);
}

void WindForceM::updateForce(RigidParticle* rp) {
    if (!rp) return;

    if (rp->isDynamic()) {
        physx::PxVec3 posPx = rp->getRigidBody()->getGlobalPose().p;
        physx::PxVec3 velPx = static_cast<physx::PxRigidDynamic*>(rp->getRigidBody())->getLinearVelocity();
        physx::PxVec3 force = calculateForce(posPx, velPx, rp->getMass());
        rp->addForce(force);
    }

}
physx::PxVec3 WindForceM::calculateForce(const physx::PxVec3& pos, const physx::PxVec3& vel, float mass)
{
    if (fabs(pos.x - _areaCenter.x) > _areaHalfSize.x ||
        fabs(pos.y - _areaCenter.y) > _areaHalfSize.y ||
        fabs(pos.z - _areaCenter.z) > _areaHalfSize.z)
        return physx::PxVec3(0.0f);

    physx::PxVec3 vRel = _windVelocity - vel;
    float speed = vRel.magnitude();

    if (speed <= 1e-6f) return physx::PxVec3(0.0f);

    physx::PxVec3 vDir = vRel.getNormalized();

    float cosTheta = fabs(vDir.dot(_normal));
    if (cosTheta < 0.01f) cosTheta = 0.01f;

    float A_eff = _objectArea * cosTheta;

    // Formula: 0.5 * rho * C_d * A * v^2 (direccion vDir)
    float dragMag = 0.5f * _air_density * _dragCoeff * A_eff * speed * speed;

    return vDir * dragMag;
}