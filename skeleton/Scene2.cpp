#include "Scene2.h"
#include "Bullet.h"
#include "Entity.h"

#include "core.hpp"
#include "RenderUtils.hpp"

#include <PxPhysicsAPI.h>
#include <iostream>
using namespace physx;

Scene2::Scene2()
{
}

Scene2::~Scene2()
{
	for (auto e : gObjects) {
		delete e;
	}
}

void Scene2::update(double t)
{
	for (int i = 0; i < gObjects.size(); ++i) {
		gObjects[i]->integrate(t);
	}

}




void Scene2::render() const
{
}

void Scene2::exit()
{
}

void Scene2::enter()
{
}

void Scene2::createBullet()
{

	auto cam = GetCamera();
	PxVec3 dir = cam->getDir();
	Bullet* bull = new Bullet(cam->getTransform().p,  Vector3(dir.x, dir.y, dir.z).getNormalized(), Vector3(0, -4.8, 0), 10.0);
	gObjects.push_back(bull);
	/*std::cout << "Creadno\n";
	Particle* part = new Particle(Vector3(0,0,0), Vector3(5,10,0), Vector3(0,-9.8,0), INTEGRATETYPES::EULER);
	gObjects.push_back(part);*/

}