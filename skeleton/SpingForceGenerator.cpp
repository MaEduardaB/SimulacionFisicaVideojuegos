#include "SpingForceGenerator.h"
#include "Particle.h"

SpingForceGenerator::SpingForceGenerator(Particle* other, double k, double resting_length)	:
	_k(k), _other(other), _resting_length(resting_length)
{	
}

void SpingForceGenerator::updateForce(Particle* p)
{
	if(p)
		p->addForce(calculateForce(p));
}

Vector3 SpingForceGenerator::calculateForce(Particle* p)
{
	Vector3 relative_pos_vector = _other->getTransform().p - p->getTransform().p;
	Vector3 force;

	const float length = relative_pos_vector.normalize();
	const float delta_x = length - _resting_length;

	Vector3 force = relative_pos_vector * delta_x * _k;
	return force;
}
