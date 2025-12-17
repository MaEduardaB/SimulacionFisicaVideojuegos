#include "SpringForceGenerator.h"
#include "Particle.h"

SpringForceGenerator::SpringForceGenerator(Particle* other, double k, double resting_length)	:
	_k(k), _other(other), _resting_length(resting_length)
{	
}

void SpringForceGenerator::updateForce(Particle* p)
{
	if(p)
		p->addForce(calculateForce(p->getTransform().p, p->getVelocity(), p->getMass()));
}

void SpringForceGenerator::updateForce(physx::PxRigidDynamic *rb)
{
	if (!rb) return;
	physx::PxVec3 posPx = rb->getGlobalPose().p;
	physx::PxVec3 velPx = rb->getLinearVelocity();
	Vector3 pos(posPx.x, posPx.y, posPx.z);
	Vector3 vel(velPx.x, velPx.y, velPx.z);
	Vector3 force = calculateForce(pos, vel, rb->getMass());
	rb->addForce(physx::PxVec3(force.x, force.y, force.z));
}

Vector3 SpringForceGenerator::calculateForce(const Vector3& pos, const Vector3& vel, float mass)
{
	Vector3 relative_pos_vector = _other->getTransform().p - pos;

	const float length = relative_pos_vector.normalize();
	const float delta_x = length - _resting_length;
	Vector3 force = relative_pos_vector * delta_x * _k;
	return force;
}
