#include "TorbellinoForce.h"
#include "Particle.h"
#include <cmath>
#include <algorithm>

TorbellinoForce::TorbellinoForce(const Vector3& center,
    float radius,
    float K,
    float airDensity)
    : _center(center),
    _radius(radius),
    _K(K),
    _air_density(airDensity)
{
}


void TorbellinoForce::setParameters(float K, float radius)
{
    _K = K;
    _radius = radius;
}

void TorbellinoForce::setArea(const Vector3& center, float radius)
{
    _center = center;
    _radius = radius;
}
void TorbellinoForce::updateForce(physx::PxRigidDynamic* rb) {
    if (!rb) return;
    physx::PxVec3 posPx = rb->getGlobalPose().p;
    physx::PxVec3 velPx = rb->getLinearVelocity();
    Vector3 pos(posPx.x, posPx.y, posPx.z);
    Vector3 vel(velPx.x, velPx.y, velPx.z);
    Vector3 force = calculateForce(pos, vel, rb->getMass());
    rb->addForce(physx::PxVec3(force.x, force.y, force.z));
}

Vector3 TorbellinoForce::updateForces(Particle* p)
{
    if (!p) return Vector3(0.0f);
    return calculateForce(p->getTransform().p, p->getVelocity(), p->getMass());
}

Vector3 TorbellinoForce::calculateForce(const Vector3& pos, const Vector3& vel, float mass)
{
    Vector3 diff = pos - _center;
    float distXZ = sqrt(diff.x * diff.x + diff.z * diff.z);
    if (distXZ < 1e-4f || distXZ > _radius)
        return Vector3(0.0f);

    // viento tangencial
    Vector3 tang(-diff.z / distXZ, 0.0f, diff.x / distXZ);

    // un poco de viento hacia arriba
    float up = 1.0f - fabs(diff.y) / _radius;
    if (up < 0.0f) up = 0.0f;

    Vector3 viento = tang * (_K * distXZ) + Vector3(0.0f, up * _K, 0.0f);

    Vector3 relVel = viento - vel;
    float v = relVel.magnitude();
    if (v < 1e-5f) return Vector3(0.0f);

    Vector3 dir = relVel.getNormalized();
    float fuerza = 0.5f * _air_density * 0.6f * 0.2f * v * v;

    return dir * fuerza;
}