#include "Particle.h"
#include <PxPhysicsAPI.h>

#include <math.h>
#include <iostream>

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 ace, INTEGRATETYPES type) : Entity(pos), _velocity(vel), _aceleration(ace), _type(type)
{
	_damping = 0.98;
	_transform_ant = _transform;
}

Particle::~Particle()
{
	delete(_render);
}

void Particle::integrate(double t)
{
	physx::PxTransform _new_last_pos  = _transform;
	
	switch (_type) {
	case EULER:
		integrateEuler(t);
		break;
	case EULER_SEMI_IMPILICITO:
		integrateEuler_Semi(t);
		break;
	case VERLET:
		integrateVerlet(t);
	}

	_transform_ant = _new_last_pos;
}

void Particle::integrateEuler(double t)
{
	_transform.p = _transform.p + t * _velocity;
	_velocity += t * _aceleration;
	damp(t);
}

void Particle::integrateEuler_Semi(double t)
{
	_velocity += t * _aceleration;
	damp(t);
	_transform.p = _transform.p + t * _velocity;

}

void Particle::integrateVerlet(double t)
{
	if (_transform_ant == _transform) integrateEuler(t);
	else {
		_transform.p = 2 * _transform.p - _transform_ant.p + pow(t, 2) * _aceleration;
		damp(t);
	}
}

void Particle::damp(double t)
{
	_velocity = _velocity * pow(_damping, t);
}



void Particle::setVelocity(Vector3 newVel)
{
	_velocity = newVel;
}

void Particle::setAceleration(Vector3 newA)
{
	_aceleration = newA;
}

void Particle::setDumping(float newDum)
{
	_damping = newDum;
}

void Particle::setTime(float newTime)
{
	_lifeTIme = newTime;
}

Vector3 Particle::getVelocity() const
{
	return _velocity;
}

Vector3 Particle::getAceleration() const
{
	return _aceleration;
}

double Particle::getMass() const
{
	return _mass;
}


