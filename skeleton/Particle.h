#pragma once
#include "Entity.h"
#include "Constants.h"
using namespace physx;

class Particle : public Entity
{
public:
	Particle(PARTICLES p);
	~Particle();

	void integrate(double t) override;

	// setters

	void setVelocity(Vector3 newVel);
	void setAceleration(Vector3 newA);
	void setDumping(float newDum);
	void setTime(float newTime);

	//getters

	Vector3 getVelocity() const;
	Vector3 getAceleration() const;
	double getMass() const;
	bool getElim() const;

protected:

	void integrateEuler(double t);
	void integrateEuler_Semi(double t);
	void integrateVerlet(double t);
	void damp(double t);

	Vector3 _velocity;
	physx::PxTransform _transform_ant;

	INTEGRATETYPES _type;
	double _mass;
	Vector3 _aceleration;
	double _lifeTIme;

	double _damping;

	bool _elim;
	double _age = 0.0;
};

