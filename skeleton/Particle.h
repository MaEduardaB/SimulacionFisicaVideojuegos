#pragma once
#include "Entity.h"
#include "core.hpp"

#include <PxPhysicsAPI.h>
using namespace physx;

class RenderItem;

enum INTEGRATETYPES {
	EULER,
	EULER_SEMI_IMPILICITO,
	VERLET
};

class Particle : virtual Entity
{

public:
	Particle(Vector3 pos, Vector3 vel, Vector3 ace, INTEGRATETYPES type);
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

protected:

	void integrateEuler(double t);
	void integrateEuler_Semi(double t);
	void integrateVerlet(double t);
	void dump();

	Vector3 _velocity;
	physx::PxTransform _transform;
	physx::PxTransform _transform_ant;
	RenderItem* _render;
	INTEGRATETYPES _type;
	double _mass;
	Vector3 _aceleration;
	double _lifeTIme;

	double _dumping;
	double _dumping_time;

};

