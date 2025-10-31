#include "Particle.h"
#include <PxPhysicsAPI.h>
#include <math.h>
#include <iostream>
#include "ParticleGen.h"
#include "ParticleSystem.h"
#include "Constants.h"
#include <random>

Particle::Particle(PARTICLES p) : Entity(p._transform, Vector4(1 , 1 , 1 , 1)), _velocity(p._velocity), _mass(p._mass),
	_aceleration(p._aceleration), _type(p._type), _elim(false), _damping(p._damping), _age(0.0)
{
	_transform_ant = physx::PxTransform(p._transform);


	 static std::mt19937 mt(std::random_device{}());
    std::uniform_real_distribution<float> u01(0.0f, 1.0f);

	Vector4 color;

    switch (p._p_type)
    {
        case PARTICLE_TYPE::SPARK:
            // Tonos rojos-amarillos: R 0.8-1.0, G 0.2-7.0, B 0-0.2
            color.x = 0.8f + 0.2f * u01(mt);
            color.y = 0.2f + 0.5f * u01(mt);
            color.z = 0.2f * u01(mt);
            color.w = 1.0f;
            break;

        case PARTICLE_TYPE::FIREWORK:
            color = Vector4(0.8f, 0.5f, 0.2f, 1.0f);
            break;
        case PARTICLE_TYPE::NORMAL:
        default:
            color = Vector4(0.0f, 0.0f, 1.0f, 1.0f); // azul
            break;
    }

	setColor(color);
}

Particle::~Particle()
{
	Entity::~Entity();
}

void Particle::integrate(double t)
{
	_age += t;
	if(_age >= _lifeTIme) {
		_elim = true;
		return;
	}
	//_aceleration = _totalForce * static_cast<float>(1.0 / _mass);
	physx::PxTransform _new_last_pos  = _transform;
	//std::cout << "Integrando particula\n";
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
	//clearForces();
	_transform_ant = _new_last_pos;
}

void Particle::triggerDeath(ParticleSystem& system) const
{
    if (_onDeath)
        _onDeath(system, *this);
}

void Particle::addForce(const Vector3 &force)
{
	_totalForce += force;
}

void Particle::clearForces()
{
	_totalForce = Vector3(0.0f);
	_aceleration = Vector3(0.0f);
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

#pragma region SETTERSGETTERS
void Particle::setVelocity(Vector3 newVel)
{
	_velocity = newVel;
}

void Particle::setAceleration(Vector3 newA)
{
	_aceleration = newA;
}

void Particle::setDamping(float newDum)
{
	_damping = newDum;
}

void Particle::setTime(float newTime)
{
	_lifeTIme = newTime;
	_age = 0.0;
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

bool Particle::getElim() const
{
	return _elim;
}

void Particle::setOnDeath(std::function<void(ParticleSystem&, const Particle&)> cb)
{
    _onDeath = cb;
}

#pragma endregion
