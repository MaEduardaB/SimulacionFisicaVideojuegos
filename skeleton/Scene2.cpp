#include "Scene2.h"
#include "Bullet.h"
#include "Entity.h"

#include "core.hpp"
#include "RenderUtils.hpp"

#include <PxPhysicsAPI.h>
#include <iostream>
using namespace physx;

Scene2::Scene2(Snippets::Camera* cam): _gObjects()
{
	display_text = "Scene 2: Press 'p' to shoot light Bullet.\n Press 'b' to shoot Canon Bullet.";
    _cam = cam;
}

Scene2::~Scene2()
{
	for (auto e : _gObjects) {
		delete e;
	}
}

void Scene2::update(double t)
{
	for (int i = 0; i < _gObjects.size(); ++i) {
		_gObjects[i]->integrate(t);
	}

}

void Scene2::render() const
{
}

void Scene2::exit()
{
    for (auto e : _gObjects) {
		delete e;
	}
	_gObjects.clear();

}

void Scene2::enter()
{
}

void Scene2::keyPressed(unsigned char key)
{

    auto cam = GetCamera();
    PxVec3 dir = cam->getDir().getNormalized();

    double masaReal = 0.008;     // kg 
    double velReal = 380.0;      // m/s
    double velSim = 25.0;        // m/s
    Vector3 gravedad(0, -4.8, 0);

    Bullet* bull = new Bullet(
        cam->getTransform().p,
        Vector3(dir.x, dir.y, dir.z),
        masaReal,
        velReal,
        velSim,
        gravedad
    );

    Bullet* bull2 = new Bullet(
        cam->getTransform().p,
        Vector3(dir.x, dir.y, dir.z),
        masaReal + 100,
        velReal,
        velSim,
        gravedad
    );

    _gObjects.push_back(bull);
    _gObjects.push_back(bull2);
}