#include "Scene1.h"
#include "Particle.h"
#include "Entity.h"

#include "core.hpp"

#include <PxPhysicsAPI.h>
#include <iostream>
using namespace physx;

Scene1::Scene1()
{
}

Scene1::~Scene1()
{
	for (auto e : gObjects) {
		delete e;
	}
}

void Scene1::update(double t)
{
	for (int i = 0; i < gObjects.size(); ++i) {
		gObjects[i]->integrate(t);
	}

}




void Scene1::render() const
{
}

void Scene1::exit()
{
}

void Scene1::enter()
{
}

void Scene1::createParticle()
{
	std::cout << "Creadno\n";
	Particle* part = new Particle(Vector3(0,0,0), Vector3(5,10,0), Vector3(0,-9.8,0), INTEGRATETYPES::EULER);
	gObjects.push_back(part);

}