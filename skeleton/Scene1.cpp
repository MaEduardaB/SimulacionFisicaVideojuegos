#include "Scene1.h"
#include "Particle.h"
#include "Entity.h"

#include "core.hpp"

#include <PxPhysicsAPI.h>
#include <iostream>
using namespace physx;

Scene1::Scene1(): _gObjects()
{
}

Scene1::~Scene1()
{
	for (auto e : _gObjects) {
		delete e;
	}
}

void Scene1::update(double t)
{
	for (int i = 0; i < _gObjects.size(); ++i) {
		_gObjects[i]->integrate(t);
	}

}

void Scene1::render() const
{
}

void Scene1::exit()
{
	for (auto e : _gObjects) {
		delete e;
	}
	_gObjects.clear();
}

void Scene1::enter()
{
}

void Scene1::create()
{
	//std::cout << "Creadno\n";
	PARTICLES prop;
		prop._velocity = Vector3(5,10,0);
		prop._aceleration =  Vector3(0,-9.8,0);
		prop._transform = Vector3(0,0,0);
		prop._mass = 1.0;
		prop._damping = 0.99;
		prop._type = INTEGRATETYPES::EULER_SEMI_IMPILICITO;

	Particle* part = new Particle(prop);
	_gObjects.push_back(part);

}