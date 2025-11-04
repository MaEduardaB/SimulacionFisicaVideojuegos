#pragma once
#include<list>
#include<memory>
#include <PxPhysicsAPI.h>
#include "core.hpp"
class Particle;
class ParticleGen;
class ForceRegestry;
class GravityForce;
class WindForce;
class WindForceM;
class ForceGenerator;
class TorbellinoForce;
class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	void update(double t);
	void addGenerator(ParticleGen* gen);
	void addForce();
	void createParticles();
	void clearForces();
	void addParticle(Particle* p, bool applyGravity = true);
	const std::list<std::unique_ptr<Particle>>& getParticles() const;
	void createGravity();
	void createWind(const Vector3& windVelocity,
					const Vector3& areaCenter,
					const Vector3& areaHalfSize,
					float k1 = 1.0f,
					float k2 = 0.0f);

	void createTorbellino(const Vector3& center,
		float radio,
		float intensidad);

protected:
	void generateGravityForce(const std::list<Particle*>& newParticles);
	void generateWindForce(const std::list<Particle*>& newParticles);
	void generateTorbellinoForce(const std::list<Particle*>& newParticles);
	void generateGravityForce(const std::list<std::unique_ptr<Particle>>& newParticles);



	std::list<std::unique_ptr<Particle>> _particles; // lista de particulas del sistema
	std::list<ParticleGen*> _generators; // lista de generadores de particulas

	// lista de fuerzas que se aplican a todas las particulas de ese sistema
	std::list<Particle*> _newParticles;

	//std::list<ForceGenerator*> _force_generators;
	std::unique_ptr<GravityForce> _gravityForce;
	std::unique_ptr<WindForce> _windForce;
	std::unique_ptr<WindForceM> _windForceM;
	std::unique_ptr<TorbellinoForce> _torbellinoForce;

	ForceRegestry* _force_registry;

};

