#include "Scene2.h"
#include "Bullet.h"
#include "GravityForce.h"
#include "ForceRegestry.h"
#include "core.hpp"
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
#include <iostream>
#include "SceneManager.h"
#include "RenderUtils.hpp"
#include "Constants.h"
using namespace physx;

Scene2::Scene2(Snippets::Camera* cam) : _gObjects()
{
    display_text = "Scene 2: Press 'p' to shoot light Bullet.\nPress 'b' to shoot Canon Bullet.";
    _cam = cam;
    _force_registry = nullptr;
    _gravity = nullptr;
}

Scene2::~Scene2()
{
    for (auto e : _gObjects)
        delete e;

    delete _force_registry;
    delete _gravity;

    _cam = nullptr;
}

void Scene2::update(double t)
{
    for (auto* b : _gObjects) {
        _gravity->updateForce(b);
        b->integrate(t);
    }
}

void Scene2::render() const
{
}

void Scene2::exit()
{
	_force_registry->clear();
   /* for (auto e : _gObjects)
        delete e;
    _gObjects.clear();*/

    delete _force_registry;
    _force_registry = nullptr;


    DeregisterAllRenderItem();
}

void Scene2::enter()
{
    _force_registry = new ForceRegestry();
    _gravity = new GravityForce();
    _cam->setDir(PxVec3(-0.6f, -0.2f, -0.7f));
    _cam->setEye(PxVec3(50.0f, 50.0f, 50.0f));
}

void Scene2::keyPressed(unsigned char key)
{
    auto cam = GetCamera();
    PxVec3 dir = cam->getDir().getNormalized();

    double velReal = 380.0;
    double velSim = 25.0;

    Bullet* bull = nullptr;

    if(key == 'G' || key == 'g') {
		SceneManager::instance().change_to_scene(SCENE_TYPE::MAIN_MENU);
	}
	else if (key == 'p') { // bala ligera
        bull = new Bullet(Vector3(cam->getTransform().p),
                          Vector3(dir.x, dir.y, dir.z),
                          0.008, velReal, velSim);
        std::cout << "Disparada bala ligera (p)\n";
    }
    else if (key == 'b') { // bala pesada
        bull = new Bullet(Vector3(cam->getTransform().p),
                          Vector3(dir.x, dir.y, dir.z),
                          10.0, velReal, velSim);
        std::cout << "Disparada bala de cañón (b)\n";
    }

    if (bull) {
        _gObjects.push_back(bull);
        _force_registry->add(bull, _gravity);
    }
}
