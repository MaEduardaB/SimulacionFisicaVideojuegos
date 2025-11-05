#include "ParticleSystem.h"
#include "ParticleGen.h"
#include "Particle.h"
#include "GravityForce.h"
#include "WindForce.h"
#include "WindForceM.h"
#include "ForceRegestry.h"
#include "TorbellinoForce.h"
#include "ExplosionsForce.h"
#include <iostream>


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
    updateExplosions(t);

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
			std::list<Particle*> rawList = gen->generateP();

			// collect raw pointers to pass to force generation
			std::list<Particle*> rawPtrs;

			for (Particle* p : rawList) {
				if (p) {
					 bool applyGravity = (p->getParticleType() != PARTICLE_TYPE::FOG); // niebla no recibe gravedad
                    _particles.emplace_back(std::unique_ptr<Particle>(p));
                    rawPtrs.push_back(p);
                    /*if (applyGravity && _gravityForce)
                        _force_registry->add(p, _gravityForce.get());*/
				}
			}

			generateGravityForce(rawPtrs);
            generateWindForce(rawPtrs);
            generateTorbellinoForce(rawPtrs);
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

    _force_registry->add(p, _windForceM.get());

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

void ParticleSystem::createWind(const Vector3 &windVelocity, const Vector3 &areaCenter, const Vector3 &areaHalfSize, float k1, float k2)
{
    if (!_windForceM)
        _windForceM = std::make_unique<WindForceM>(windVelocity, areaCenter, areaHalfSize);
    
    _windForceM->setObjectProperties(
        80.0f,                        // area frontal (m2)
        0.5f,                        // C_D
        Vector3(0.0f, 0.0f, 1.0f)    // orientacion
    );

    for (const auto& up : _particles)
    {
        Particle* p = up.get();
        if (p)
            _force_registry->add(p, _windForceM.get());
    }
}

void ParticleSystem::createTorbellino(const Vector3& center, float radio, float intensidad)
{
    if (!_torbellinoForce)
        _torbellinoForce = std::make_unique<TorbellinoForce>(center, radio, intensidad);

    for (const auto& up : _particles)
    {
        Particle* p = up.get();
        if (p)
            _force_registry->add(p, _torbellinoForce.get());
    }
}

void ParticleSystem::createExplosion(const Vector3& center, float K, float radius, float decaimento, float expansionVel)
{
    auto explosion = std::make_unique<ExplosionsForce>(center, K, radius, decaimento, expansionVel);

    for (const auto& up : _particles)
    {
        Particle* p = up.get();
        if (p)
            _force_registry->add(p, explosion.get());
    }

    _explosions.push_back(std::move(explosion));
}

void ParticleSystem::updateExplosions(float dt)
{
    for (auto it = _explosions.begin(); it != _explosions.end(); )
    {
        ExplosionsForce* e = it->get();
        e->updateTime(dt);

        if (e->hasFaded())
        {
            // Eliminar del ForceRegistry antes de borrar la fuerza
            _force_registry->removeForce(e);
            it = _explosions.erase(it);
            std::cout << "elim Explosion\n";
        }
        else
        {
            ++it;
        }
    }
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

void ParticleSystem::generateWindForce(const std::list<Particle*>& newParticles)
{
    if (!_windForceM)
        return;

    for (auto p : newParticles)
    {
        if (p)
            _force_registry->add(p, _windForceM.get());
    }
}

void ParticleSystem::generateTorbellinoForce(const std::list<Particle*>& newParticles)
{
    if (!_torbellinoForce)
        return;

    for (auto p : newParticles)
    {
        if (p)
            _force_registry->add(p, _torbellinoForce.get());
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
