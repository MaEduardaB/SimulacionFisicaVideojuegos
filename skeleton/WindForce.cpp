#include "WindForce.h"
#include "Particle.h"

WindForce::WindForce(const Vector3& windVelocity,
                     const Vector3& areaCenter,
                     const Vector3& areaHalfSize,
                     float k1, float k2)
    : _windVelocity(windVelocity),
      _areaCenter(areaCenter),
      _areaHalfSize(areaHalfSize),
      _k1(k1), _k2(k2)
{
}

bool WindForce::isInsideArea(const Vector3& pos) const
{
    return (fabs(pos.x - _areaCenter.x) <= _areaHalfSize.x &&
            fabs(pos.y - _areaCenter.y) <= _areaHalfSize.y &&
            fabs(pos.z - _areaCenter.z) <= _areaHalfSize.z);
}

void WindForce::updateForce(Particle* p)
{
    if (!isInsideArea(p->getTransform().p) || !_active) return;
    
    p->addForce(calculateForce(p->getTransform().p, p->getVelocity(), p->getMass()));
}

void WindForce::updateForce(physx::PxRigidDynamic* rb) {
    if (!rb) return;
    physx::PxVec3 posPx = rb->getGlobalPose().p;
    physx::PxVec3 velPx = rb->getLinearVelocity();
    Vector3 pos(posPx.x, posPx.y, posPx.z);
    Vector3 vel(velPx.x, velPx.y, velPx.z);

    
    Vector3 force = calculateForce(pos, vel, rb->getMass());
    rb->addForce(physx::PxVec3(force.x, force.y, force.z));
}

physx::PxVec3 WindForce::calculateForce(const physx::PxVec3 &pos, const physx::PxVec3 &vel, float mass)
{
    if (!isInsideArea(pos) || !_active) return Vector3(0, 0, 0);
    
    Vector3 relVel = _windVelocity - vel;
    Vector3 force = _k1 * relVel;

    if (_k2 != 0.0f)
        force += _k2 * relVel.magnitude() * relVel;

    return physx::PxVec3(force.x, force.y, force.z);
}
