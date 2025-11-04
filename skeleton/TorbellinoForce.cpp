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

void TorbellinoForce::updateForce(Particle* p)
{
    if (!p) return;

    Vector3 force = calculateForce(p);
    p->addForce(force);
}

Vector3 TorbellinoForce::calculateForce(Particle* p)
{
    Vector3 pos = p->getTransform().p;
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

    Vector3 relVel = viento - p->getVelocity();
    float vel = relVel.magnitude();
    if (vel < 1e-5f) return Vector3(0.0f);

    Vector3 dir = relVel.getNormalized();
    float fuerza = 0.5f * _air_density * 0.6f * 0.2f * vel * vel;

    return dir * fuerza;
}