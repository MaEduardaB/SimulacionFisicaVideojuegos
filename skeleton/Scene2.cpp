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
    PxVec3 dir = cam->getDir().getNormalized();

    double masaReal = 0.008;     // kg 
    double velReal = 380.0;      // m/s
    double velSim = 50.0;        // m/s
    Vector3 gravedad(0, -4.8, 0);

    Bullet* bull = new Bullet(
        cam->getTransform().p,
        Vector3(dir.x, dir.y, dir.z),
        masaReal,
        velReal,
        velSim,
        gravedad
    );

    gObjects.push_back(bull);
}