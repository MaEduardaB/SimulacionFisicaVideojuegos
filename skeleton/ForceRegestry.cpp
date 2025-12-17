#include "Constants.h"
#include "Particle.h"
#include "ForceRegestry.h"
#include "ForceGenerator.h"
ForceRegestry::ForceRegestry() : _registryParticles(), _registryRigids()
{

}

void ForceRegestry::add(Particle* p, ForceGenerator* fg)
{
    if (p && fg)
        _registryParticles.emplace_back(p, fg);
}

void ForceRegestry::add(physx::PxRigidActor *p, ForceGenerator *fg)
{
    if (!p || !fg) return;
    auto dyn = p->is<physx::PxRigidDynamic>();
    if (!dyn) return;
    _registryRigids.emplace_back(p, fg);
}

void ForceRegestry::remove(Particle* p, ForceGenerator* fg)
{
    _registryParticles.remove_if([&](const std::pair<Particle*, ForceGenerator*>& reg) {
        bool sameP = (!p || reg.first == p);
        bool sameF = (!fg || reg.second == fg);
        return sameP && sameF;
    });
}

void ForceRegestry::remove(physx::PxRigidActor *p, ForceGenerator *fg)
{
    _registryRigids.remove_if([&](const std::pair<physx::PxRigidActor*, ForceGenerator*>& reg) {
        bool sameP = (!p || reg.first == p);
        bool sameF = (!fg || reg.second == fg);
        return sameP && sameF;
    });
}

void ForceRegestry::clear()
{
    _registryParticles.clear();
    _registryRigids.clear();
}

void ForceRegestry::updateForces()
{
    for (auto& entry : _registryParticles) {
        Particle* p = entry.first;
        ForceGenerator* fg = entry.second;
        if (p && fg) {
            fg->updateForce(p);
        }
    }
    for (auto& entry : _registryRigids) {
        physx::PxRigidActor* p = entry.first;
        ForceGenerator* fg = entry.second;
        if (p && fg) {
            fg->updateForce(static_cast<physx::PxRigidDynamic*>(p));
        }
    }
}


void ForceRegestry::removeForce(ForceGenerator* fg)
{
    for (auto it = _registryParticles.begin(); it != _registryParticles.end(); )
    {
        if (it->second == fg)
            it = _registryParticles.erase(it);
        else
            ++it;
    }
    for (auto it = _registryRigids.begin(); it != _registryRigids.end(); )
    {
        if (it->second == fg)
            it = _registryRigids.erase(it);
        else
            ++it;
    }
}

void ForceRegestry::removeInvalid(const std::list<std::unique_ptr<Particle>>& particles)
{
    _registryParticles.remove_if([&](const std::pair<Particle*, ForceGenerator*>& entry) {
        Particle* p = entry.first;
        // Verifica si el puntero sigue existiendo en la lista de partículas
        bool alive = false;
        for (const auto& up : particles) {
            if (up.get() == p) {
                alive = true;
                break;
            }
        }
        return !alive; // elimina si ya no existe
    });
}

void ForceRegestry::removeInvalid(const std::list<std::unique_ptr<physx::PxRigidActor>>& particles)
{
    _registryRigids.remove_if([&](const std::pair<physx::PxRigidActor*, ForceGenerator*>& entry) {
        physx::PxRigidActor* p = entry.first;
        // Verifica si el puntero sigue existiendo en la lista de partículas
        bool alive = false;
        for (const auto& up : particles) {
            if (up.get() == p) {
                alive = true;
                break;
            }
        }
        return !alive; // elimina si ya no existe
    });
}