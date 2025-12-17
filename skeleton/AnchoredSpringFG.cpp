#include "AnchoredSpringFG.h"
#include "Particle.h"
#include "Constants.h"

AnchoredSpringFG::AnchoredSpringFG(double k, double resting_length, const Vector3& _anchorPos): SpringForceGenerator(nullptr, k, resting_length)
{	
	PARTICLES prop;
	prop._transform = _anchorPos;
	prop._velocity = Vector3(0.0f);
	prop._aceleration = Vector3(0.0f);
	prop._type = INTEGRATETYPES::EULER_SEMI_IMPILICITO;
	prop._p_type = PARTICLE_TYPE::NORMAL;
	prop._mass = 0.0;
	prop._shapeType = "BOX";
	prop._size = 2.0f;

	_other = new Particle(prop);
}

AnchoredSpringFG::~AnchoredSpringFG()
{
	delete _other;
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

Vector3 AnchoredSpringFG::calculateForce(const Vector3& pos, const Vector3& vel, float mass)
{
	Vector3 relative_pos_vector = _other->getTransform().p - pos;

	const float length = relative_pos_vector.normalize();
	const float delta_x = length - _resting_length;
	Vector3 force = relative_pos_vector * delta_x * _k;
	return force;
}
