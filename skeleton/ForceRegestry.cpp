#include "Constants.h"
#include "Particle.h"
#include "ForceRegestry.h"
#include "ForceGenerator.h"
ForceRegestry::ForceRegestry() : _registry()
{

}

void ForceRegestry::add(Particle *p, ForceGenerator *fg)
{
    _registry.push_back(std::make_pair(p, fg));
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
        fg->updateForce(p);
    }
}
