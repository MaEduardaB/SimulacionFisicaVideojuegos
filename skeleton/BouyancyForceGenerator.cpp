#include "BouyancyForceGenerator.h"
#include "Particle.h"

BouyancyForceGenerator::BouyancyForceGenerator(float h, float v, float d, float posWater):
	_height(h), _volume(v), _liquid_density(d), _posWater(posWater)
{	
}


void BouyancyForceGenerator::updateForce(physx::PxRigidDynamic* rb) {
    if (!rb) return;
    physx::PxVec3 posPx = rb->getGlobalPose().p;
    Vector3 pos(posPx.x, posPx.y, posPx.z);
    Vector3 force = calculateForce(pos, Vector3(0,0,0), rb->getMass());
    rb->addForce(physx::PxVec3(force.x, force.y, force.z));
}

Vector3 BouyancyForceGenerator::calculateForce(Particle* p)
{
    if (!p) return Vector3(0,0,0);
    return calculateForce(p->getTransform().p, p->getVelocity(), p->getMass());
}

Vector3 BouyancyForceGenerator::calculateForce(const Vector3& pos, const Vector3& vel, float mass)
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

    return Vector3(0, _liquid_density * _volume * immersed * 9.8f, 0);
}