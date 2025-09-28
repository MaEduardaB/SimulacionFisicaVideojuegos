#include "Scene1.h"
#include "Particle.h"
#include "Entity.h"

#include "core.hpp"

#include <PxPhysicsAPI.h>
using namespace physx;

void Scene1::createParticle()
{
	gObjects.push_back(static_cast<Entity>( new Particle(Vector3(), Vector3(), Vector3(), INTEGRATETYPES::EULER)));

}