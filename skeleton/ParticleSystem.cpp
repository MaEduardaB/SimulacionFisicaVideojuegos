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
	_force_registry->updateForces();
	for (auto it = _particles.begin(); it != _particles.end(); )
    {
        Particle* p = it->get();
        if (p != nullptr) {
            p->integrate(t);

            if (p->getElim()) {
                p->triggerDeath(*this);
                it = _particles.erase(it);
            } else {
                ++it;
            }
        } else {
            it = _particles.erase(it);
        }
    }

    _force_registry->removeInvalid(_particles);

}

void ParticleSystem::addGenerator(ParticleGen* gen)
{
	if (gen)
		_generators.push_back(gen);
}

void ParticleSystem::addForce()
{
}

void ParticleSystem::createParticles()
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
					 bool applyGravity = (p->getParticleType() != PARTICLE_TYPE::FOG); // niebla no recibe gravedad
                    _particles.emplace_back(std::unique_ptr<Particle>(p));

                    if (applyGravity && _gravityForce)
                        _force_registry->add(p, _gravityForce.get());
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

void ParticleSystem::addParticle(Particle* p, bool applyGravity)
{
	if (p)
		_particles.emplace_back(std::unique_ptr<Particle>(p));

	if (applyGravity && _gravityForce)
        _force_registry->add(p, _gravityForce.get());
}

const std::list<std::unique_ptr<Particle>>& ParticleSystem::getParticles() const
{
	return _particles;
}

void ParticleSystem::createGravity()
{
	 if (!_gravityForce)
        _gravityForce = std::make_unique<GravityForce>();

	generateGravityForce(_particles);
}

void ParticleSystem::generateGravityForce(const std::list<Particle*>& newParticles)
{
	if (!_gravityForce)
        return;

    for (auto p : newParticles)
    {
        if (p)
            _force_registry->add(p, _gravityForce.get());
    }
}

void ParticleSystem::generateGravityForce(const std::list<std::unique_ptr<Particle>>& newParticles)
{
	if (!_gravityForce)
        return;

    for (const auto& up : newParticles)
    {
        Particle* p = up.get();
        if (p)
            _force_registry->add(p, _gravityForce.get());
    }
}
