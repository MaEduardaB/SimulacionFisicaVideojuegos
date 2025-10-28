#pragma once
#include "Entity.h"
#include "Constants.h"
#include <functional>

using namespace physx;
class ParticleSystem;
class Particle : public Entity
{
public:
	Particle(PARTICLES p);
	~Particle();

	void integrate(double t) override;

	// --- Setters ---
    void setVelocity(Vector3 newVel);
    void setAceleration(Vector3 newA);
    void setDamping(float newDamp);
    void setTime(float newTime);

    // --- Getters ---
    Vector3 getVelocity() const;
    Vector3 getAceleration() const;
    double getMass() const;
    bool getElim() const;
    const PxTransform& getTransform() const { return _transform; }

    // --- Callbacks ---
    void setOnDeath(std::function<void(ParticleSystem&, const Particle&)> cb);
    void triggerDeath(ParticleSystem& sys) const;

protected:
	// --- Callback al morir ---
    std::function<void(ParticleSystem&, const Particle&)> _onDeath;

    // --- Métodos de integración ---
    void integrateEuler(double t);
    void integrateEuler_Semi(double t);
    void integrateVerlet(double t);
    void damp(double t);


	// --- Propiedades físicas ---
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

