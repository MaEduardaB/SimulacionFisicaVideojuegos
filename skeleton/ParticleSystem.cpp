#include "ParticleSystem.h"
#include "ParticleGen.h"
#include "Particle.h"
#include "GravityForce.h"
#include "ForceRegestry.h"

ParticleSystem::ParticleSystem() : _particles(), _generators(), _force_registry(new ForceRegestry()), _gravityForce(nullptr)
{
}

ParticleSystem::~ParticleSystem()
{
	// _particles stores unique_ptrs so they will be deleted automatically
	_particles.clear();
}

void ParticleSystem::update(double t)
{
	for (auto it = _particles.begin(); it != _particles.end(); )
	{
		Particle* p = it->get();
		if (p != nullptr) {
			p->integrate(t);

			if (p->getElim()) {
				p->triggerDeath(*this);

				it = _particles.erase(it); // unique_ptr destructor frees memory
			}
			else {
				++it;
			}
		}
		else {
			it = _particles.erase(it);
		}
	}
	_force_registry->updateForces();
}

void ParticleSystem::addGenerator(ParticleGen* gen)
{
	if (gen)
		_generators.push_back(gen);
}

void ParticleSystem::addForce()
{
}

void ParticleSystem::cleanParticles()
{
	for (auto it = _generators.begin(); it != _generators.end(); ++it)
	{
		ParticleGen* gen = *it;                   
		if (gen != nullptr) {
			// gen->generateP() returns a list of raw Particle*; wrap them into unique_ptr
			std::list<Particle*> rawList = gen->generateP();

			// collect raw pointers to pass to force generation
			std::list<Particle*> rawPtrs;

			for (Particle* p : rawList) {
				if (p) {
					rawPtrs.push_back(p);
					_particles.emplace_back(std::unique_ptr<Particle>(p));
				}
			}

			// now setup gravity forces for the newly added particles
			generateGravityForce(rawPtrs);
		}
	}
}

void ParticleSystem::clearForces()
{
}

void ParticleSystem::addParticle(Particle* p)
{
	if (p)
		_particles.emplace_back(std::unique_ptr<Particle>(p));
}

const std::list<std::unique_ptr<Particle>>& ParticleSystem::getParticles() const
{
	return _particles;
}

void ParticleSystem::createGravity()
{
	_gravityForce = new GravityForce();
	generateGravityForce(_particles);
}

void ParticleSystem::generateGravityForce(const std::list<Particle*>& newParticles)
{
	for (auto p : newParticles) {
		if (p)
			_force_registry->add(p, _gravityForce);
	}
}

void ParticleSystem::generateGravityForce(const std::list<std::unique_ptr<Particle>>& newParticles)
{
	for (const auto& up : newParticles) {
		Particle* p = up.get();
		if (p)
			_force_registry->add(p, _gravityForce);
	}
}
