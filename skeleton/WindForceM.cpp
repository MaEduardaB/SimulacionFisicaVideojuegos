// WindForceM.cpp
#include "WindForceM.h"
#include "Particle.h"
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

    if (fabs(pos.x - _areaCenter.x) > _areaHalfSize.x ||
        fabs(pos.y - _areaCenter.y) > _areaHalfSize.y ||
        fabs(pos.z - _areaCenter.z) > _areaHalfSize.z)
        return;

    Vector3 f = calculateForce(pos, p->getVelocity(), p->getMass());
    p->addForce(f);
}

void WindForceM::updateForce(physx::PxRigidDynamic* rb) {
    if (!rb) return;
    physx::PxVec3 posPx = rb->getGlobalPose().p;
    physx::PxVec3 velPx = rb->getLinearVelocity();
    Vector3 pos(posPx.x, posPx.y, posPx.z);
    Vector3 vel(velPx.x, velPx.y, velPx.z);
    Vector3 force = calculateForce(pos, vel, rb->getMass());
    rb->addForce(physx::PxVec3(force.x, force.y, force.z));
}

Vector3 WindForceM::calculateForce(const Vector3& pos, const Vector3& vel, float mass)
{
    if (fabs(pos.x - _areaCenter.x) > _areaHalfSize.x ||
        fabs(pos.y - _areaCenter.y) > _areaHalfSize.y ||
        fabs(pos.z - _areaCenter.z) > _areaHalfSize.z)
        return Vector3(0.0f);

    Vector3 vRel = _windVelocity - vel;
    float speed = vRel.magnitude();

    if (speed <= 1e-6f) return Vector3(0.0f);

    Vector3 vDir = vRel.getNormalized();

    float cosTheta = fabs(vDir.dot(_normal));
    if (cosTheta < 0.01f) cosTheta = 0.01f;

    float A_eff = _objectArea * cosTheta;

    // Formula: 0.5 * rho * C_d * A * v^2 (direccion vDir)
    float dragMag = 0.5f * _air_density * _dragCoeff * A_eff * speed * speed;

    return vDir * dragMag;
}