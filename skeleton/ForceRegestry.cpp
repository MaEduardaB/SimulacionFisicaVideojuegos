#include "Constants.h"
#include "Particle.h"
#include "ForceRegestry.h"
#include "ForceGenerator.h"
ForceRegestry::ForceRegestry() : _registry()
{

}

void ForceRegestry::add(Particle* p, ForceGenerator* fg)
{
    if (p && fg)
        _registry.emplace_back(p, fg);
}

void ForceRegestry::remove(Particle* p, ForceGenerator* fg)
{
    _registry.remove_if([&](const std::pair<Particle*, ForceGenerator*>& reg) {
        bool sameP = (!p || reg.first == p);
        bool sameF = (!fg || reg.second == fg);
        return sameP && sameF;
    });
}

void ForceRegestry::clear()
{
    _registry.clear();
}

void ForceRegestry::updateForces()
{
    for (auto& entry : _registry) {
        Particle* p = entry.first;
        ForceGenerator* fg = entry.second;
        if (p && fg) {
            fg->updateForce(p);
        }
    }
}

void ForceRegestry::removeInvalid(const std::list<std::unique_ptr<Particle>>& particles)
{
    _registry.remove_if([&](const std::pair<Particle*, ForceGenerator*>& entry) {
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