#pragma once
#include<list>
#include<memory>

class Particle;
class ParticleGen;
class ForceRegestry;
class GravityForce;
class ForceGenerator;
class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	void update(double t);
	void addGenerator(ParticleGen* gen);
	void addForce();
	void cleanParticles();
	void clearForces();
	void addParticle(Particle* p);
	const std::list<std::unique_ptr<Particle>>& getParticles() const;
	void createGravity();
protected:
	void generateGravityForce(const std::list<Particle*>& newParticles);
	void generateGravityForce(const std::list<std::unique_ptr<Particle>>& newParticles);



	std::list<std::unique_ptr<Particle>> _particles; // lista de particulas del sistema
	std::list<ParticleGen*> _generators; // lista de generadores de particulas

	// lista de fuerzas que se aplican a todas las particulas de ese sistema
	std::list<Particle*> _newParticles;

	//std::list<ForceGenerator*> _force_generators;
	GravityForce* _gravityForce;
	ForceRegestry* _force_registry;

};

