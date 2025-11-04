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
    if (!isInsideArea(p->getTransform().p)) return;
    p->addForce(calculateForce(p));
}

Vector3 WindForce::calculateForce(Particle* p)
{
    Vector3 relVel = _windVelocity - p->getVelocity();
    Vector3 force = _k1 * relVel;

    if (_k2 != 0.0f)
        force += _k2 * relVel.magnitude() * relVel;

    return force;
}