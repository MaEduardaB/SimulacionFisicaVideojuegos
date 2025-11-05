#include "ExplosionsForce.h"
#include "Particle.h"


ExplosionsForce::ExplosionsForce(const Vector3& center, float K, float radius, float tau, float expansionVel)
    :_center(center), _K(K), _R(radius), _decaimento(tau), _expVel(expansionVel), _time(0.0f) {}


void ExplosionsForce::updateForce(Particle* p) {
    if (!p) return;

    Vector3 f = calculateForce(p);

    p->addForce(f);
}

Vector3 ExplosionsForce::calculateForce(Particle* p)
{
    Vector3 pos = p->getTransform().p;
    Vector3 dif = pos - _center;
    float dist = dif.magnitude();

    if (dist > _R) return Vector3(); // fuera del rango

    Vector3 dir = dif;
    dir.normalize();

    float f = _K / (dist * dist + 0.0001f);
    f *= exp(-_time / _decaimento);

    return dir * f;
}

void ExplosionsForce::updateTime(float dt) {
    _time += dt;
    if (_expVel > 0.0f) _R += _expVel * dt; // crecer
}

bool ExplosionsForce::hasFaded() const {
    return _time > 4.0f * _decaimento;
}