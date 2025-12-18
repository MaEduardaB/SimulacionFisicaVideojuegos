#include "AnchoredSpringFG.h"
#include "Particle.h"
#include "RigidParticle.h"
#include "Constants.h"

AnchoredSpringFG::AnchoredSpringFG(double k, double resting_length, const Vector3& _anchorPos): SpringForceGenerator(static_cast<RigidParticle*>(nullptr), k, resting_length)
{	
	RIGID_BODY_PROPS prop;
	prop._transform = _anchorPos;
	prop._velocity = Vector3(0.0f);
	prop._mass = 0.0;
	prop._sizeX = 20.0f;
	prop._sizeY = 20.0f;
	prop._sizeZ = 20.0f;
	prop._lifeTime = 10000;
	prop._shapeType = "BOX";
	prop._isDynamic = false;

	_isRigid = true;
	_otherRigid = new RigidParticle(prop);
}

AnchoredSpringFG::~AnchoredSpringFG()
{
	delete _otherRigid;
}

void AnchoredSpringFG::updateForce(Particle* p)
{
	if(p)
		p->addForce(calculateForce(p->getTransform().p, p->getVelocity(), p->getMass()));
}

void AnchoredSpringFG::updateForce(physx::PxRigidDynamic *rb)
{
	if (!rb) return;
	physx::PxVec3 posPx = rb->getGlobalPose().p;
	physx::PxVec3 velPx = rb->getLinearVelocity();
	Vector3 pos(posPx.x, posPx.y, posPx.z);
	Vector3 vel(velPx.x, velPx.y, velPx.z);
	Vector3 force = calculateForce(pos, vel, rb->getMass());
	rb->addForce(physx::PxVec3(force.x, force.y, force.z));
}

void AnchoredSpringFG::updateForce(RigidParticle* rp) {
    if (!rp || !rp->isDynamic()) return;
    physx::PxVec3 posPx = rp->getRigidBody()->getGlobalPose().p;
    physx::PxVec3 velPx = static_cast<physx::PxRigidDynamic*>(rp->getRigidBody())->getLinearVelocity();
    physx::PxVec3 force = calculateForce(posPx, velPx, rp->getMass());
    rp->addForce(force);
}

Vector3 AnchoredSpringFG::calculateForce(const Vector3& pos, const Vector3& vel, float mass)
{
	Vector3 otherPos = _isRigid ? _otherRigid->getPosition() : _otherParticle->getTransform().p;
	Vector3 relative_pos_vector = otherPos - pos;

	const float length = relative_pos_vector.normalize();
	const float delta_x = length - _resting_length;
	Vector3 force = relative_pos_vector * delta_x * _k;
	return force;
}
