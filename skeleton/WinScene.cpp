#include "WinScene.h"
#include "RenderUtils.hpp"
#include "SceneManager.h"
#include "Constants.h"
#include "ParticleSystem.h"
#include "FireworkGen.h"
#include <random>
#include <iostream>

WinScene::WinScene(Snippets::Camera* cam)
    : _particleSystem(nullptr), _fireworkGen(nullptr)
{
   	display_text = "Win Scene: Press 'p' to restart the game.";
    _cam = cam;
}

WinScene::~WinScene()
{
    delete _particleSystem;
    delete _fireworkGen;
}

void WinScene::enter()
{
    std::cout << "[WinScene]\n";

	_cam->setDir(physx::PxVec3(-0.6f,-0.2f,-0.7f));
	_cam->setEye(physx::PxVec3(50.0f, 50.0f, 50.0f));

    _particleSystem = new ParticleSystem();

    Vector3 initVel(0.0f, 0.0f, 0.0f);
    Vector3 initPos(0.0f, 0.0f, 0.0f);
    _fireworkGen = new FireworkGen(std::mt19937(std::random_device{}()), initVel, initPos, 1.0, 0.9, 20);

    _particleSystem->addGenerator(_fireworkGen);
}

void WinScene::update(double t)
{
    if (!_particleSystem || !_fireworkGen) return;

    _timer += t;
    if (_timer >= _interval)
    {
        _timer = 0.0;

        auto particles = _fireworkGen->generateP();
        for (auto p : particles)
        {
            _particleSystem->addParticle(p);
        }
    }

    _particleSystem->update(t);
}

void WinScene::render() const
{
}

void WinScene::exit()
{
    delete _particleSystem;
    _particleSystem = nullptr;

    delete _fireworkGen;
    _fireworkGen = nullptr;
}

void WinScene::keyPressed(unsigned char key)
{
    if(key == 'G' || key == 'g') {
		SceneManager::instance().change_to_scene(SCENE_TYPE::MAIN_MENU);
	}else if (key == 'p' || key == 'P')
    {
        std::cout << "Cambiando a GameScene\n";
        SceneManager::instance().change_to_scene(SCENE_TYPE::GAME);
    }
}
