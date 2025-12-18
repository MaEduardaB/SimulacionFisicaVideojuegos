#include "ExplosionsForce.h"
#include "Particle.h"
#include "RigidParticle.h"


ExplosionsForce::ExplosionsForce(const Vector3& center, float K, float radius, float tau, float expansionVel)
    :_center(center), _K(K), _R(radius), _decaimento(tau), _expVel(expansionVel), _time(0.0f) {}


void ExplosionsForce::updateForce(Particle* p) {
    if (!p) return;

    Vector3 f = calculateForce(p->getTransform().p, p->getVelocity(), p->getMass());

    p->addForce(f);
}

void ExplosionsForce::updateForce(physx::PxRigidDynamic* rb)
{
    if (!rb) return;
    physx::PxVec3 posPx = rb->getGlobalPose().p;
    physx::PxVec3 velPx = rb->getLinearVelocity();
    physx::PxVec3 force = calculateForce(posPx, velPx, rb->getMass());
    rb->addForce(force);
}

physx::PxVec3 ExplosionsForce::calculateForce(const physx::PxVec3& pos, const physx::PxVec3& vel, float mass)
{
    physx::PxVec3 dif = pos - _center;
    float dist = dif.magnitude();

    if (dist > _R) return physx::PxVec3(); // fuera del rango

    physx::PxVec3 dir = dif;
    dir.normalize();

    float f = _K / (dist * dist + 0.0001f);
    f *= exp(-_time / _decaimento);

    return dir * f;
}

void ExplosionsForce::updateForce(RigidParticle* rp) {
    if (!rp || !rp->isDynamic()) return;
    physx::PxVec3 posPx = rp->getRigidBody()->getGlobalPose().p;
    physx::PxVec3 velPx = static_cast<physx::PxRigidDynamic*>(rp->getRigidBody())->getLinearVelocity();
    physx::PxVec3 force = calculateForce(posPx, velPx, rp->getMass());
    rp->addForce(force);
}

void ExplosionsForce::updateTime(float dt) {
    _time += dt;
    if (_expVel > 0.0f) _R += _expVel * dt; // crecer
}

bool ExplosionsForce::hasFaded() const {
    return _time > 4.0f * _decaimento;
}