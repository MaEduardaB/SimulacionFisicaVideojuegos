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

ParticleSystem::ParticleSystem()
    : _particles(), _generators(), _force_registry(new ForceRegestry()), _gravityForce(nullptr)
{
}

ParticleSystem::~ParticleSystem() = default;

void ParticleSystem::update(double t)
{
    _force_registry->updateForces();
    updateExplosions(t);

    for (auto it = _particles.begin(); it != _particles.end(); )
    {
        Particle* p = it->get();
        if (p) {
            p->integrate(t);
            if (p->getElim()) {
                p->triggerDeath(*this);
                it = _particles.erase(it);
            } else ++it;
        } else it = _particles.erase(it);
    }

    _force_registry->removeInvalid(_particles);
}

void ParticleSystem::addGenerator(ParticleGen* gen)
{
    if (gen) _generators.push_back(gen);
}

void ParticleSystem::createParticles()
{
    for (auto gen : _generators)
    {
        if (!gen) continue;
        std::list<Particle*> rawList = gen->generateP();

        for (Particle* p : rawList)
        {
            if (!p) continue;
            _particles.emplace_back(std::unique_ptr<Particle>(p));
            registerAllForces(p);
        }
    }
}

void ParticleSystem::addParticle(Particle* p, bool applyGravity)
{
    if (!p) return;
    _particles.emplace_back(std::unique_ptr<Particle>(p));
    registerAllForces(p);
}

const std::list<std::unique_ptr<Particle>>& ParticleSystem::getParticles() const
{
    return _particles;
}

void ParticleSystem::createGravity()
{
    if (!_gravityForce)
        _gravityForce = std::make_unique<GravityForce>();

    for (const auto& up : _particles)
        if (Particle* p = up.get())
            _force_registry->add(p, _gravityForce.get());
}

void ParticleSystem::createWind(const Vector3& windVelocity, const Vector3& areaCenter,
                                const Vector3& areaHalfSize, float k1, float k2)
{
    auto w = std::make_unique<WindForce>(windVelocity, areaCenter, areaHalfSize, k1, k2);

    for (const auto& up : _particles)
        if (Particle* p = up.get())
            _force_registry->add(p, w.get());

    _windForces.push_back(std::move(w));
}

void ParticleSystem::createWindM(const Vector3& windVelocity, const Vector3& areaCenter,
                                 const Vector3& areaHalfSize, float airDensity, float area,
                                 float dragCoeff, const Vector3& normal)
{
    auto wm = std::make_unique<WindForceM>(windVelocity, areaCenter, areaHalfSize, airDensity);
    wm->setObjectProperties(area, dragCoeff, normal);

    for (const auto& up : _particles)
        if (Particle* p = up.get())
            _force_registry->add(p, wm.get());

    _windMForces.push_back(std::move(wm));
}

void ParticleSystem::createTorbellino(const Vector3& center, float radio, float intensidad)
{
    _torbellinoForce = std::make_unique<TorbellinoForce>(center, radio, intensidad);
    for (const auto& up : _particles)
        if (Particle* p = up.get())
            _force_registry->add(p, _torbellinoForce.get());
}

void ParticleSystem::createExplosion(const Vector3& center, float K, float radius,
                                     float decaimento, float expansionVel)
{
    auto explosion = std::make_unique<ExplosionsForce>(center, K, radius, decaimento, expansionVel);
    for (const auto& up : _particles)
        if (Particle* p = up.get())
            _force_registry->add(p, explosion.get());
    _explosions.push_back(std::move(explosion));
}

void ParticleSystem::updateExplosions(float dt)
{
    for (auto it = _explosions.begin(); it != _explosions.end(); )
    {
        ExplosionsForce* e = it->get();
        e->updateTime(dt);
        if (e->hasFaded()) {
            _force_registry->removeForce(e);
            it = _explosions.erase(it);
        } else ++it;
    }
}

void ParticleSystem::registerAllForces(Particle* p)
{
    if (!p) return;

    if (_gravityForce)
        _force_registry->add(p, _gravityForce.get());

    for (auto& w : _windForces)
        _force_registry->add(p, w.get());

    for (auto& wm : _windMForces)
        _force_registry->add(p, wm.get());

    if (_torbellinoForce)
        _force_registry->add(p, _torbellinoForce.get());
}
