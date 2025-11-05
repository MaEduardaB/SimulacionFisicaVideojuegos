#include "GameScene.h"
#include "ParticleSystem.h"
#include "GaussianGen.h"
#include "UniformGen.h"
#include "ParticleGen.h"
#include "FireworkGen.h"
#include "RainGen.h"
#include "FogGen.h"
#include "CloudSystem.h"
#include "Particle.h"
#include "WindForce.h"
#include "TorbellinoForce.h"
#include "Render/Camera.h"
#include "Render/Render.h"

#include "core.hpp"
#include "RenderUtils.hpp"

#include <PxPhysicsAPI.h>
#include <iostream>
using namespace physx;

GameScene::GameScene(Camera* cam) : _particleSystem(nullptr), _cam(cam)
{
}

GameScene::~GameScene()
{
	delete _particleSystem;

    delete _cloudSystem;
    _cloudSystem = nullptr;
}

void GameScene::enter()
{
    std::cout << "Iniciando GameScene...\n";

    _particleSystem = new ParticleSystem();

    PARTICLES prop;
    prop._transform = Vector3(0.0, 10.0, 0.0);
    prop._velocity = Vector3(0.0, 0.0f, 0.0);
    prop._aceleration = Vector3(0.0, 0.0, 0.0);
    prop._mass = 10.0;
    prop._size = 5;
    prop._damping = 0.99;
    prop._lifeTime = 10000;
    prop._type = INTEGRATETYPES::EULER_SEMI_IMPILICITO;
    prop._p_type = PARTICLE_TYPE::NORMAL;

    _player = new Particle(prop);
    _particleSystem->addParticle(_player);

    // --- Suelo ---
    RenderItem* suelo = new RenderItem(
        CreateShape(PxBoxGeometry(1000, 1, 1000)),
        new PxTransform(PxVec3(0, 0, 0)),
        Vector4(0.3f, 0.3f, 0.3f, 1.0f));

    RegisterRenderItem(suelo);
    _decoration.push_back(suelo);

    // --- Pared en eje X (pared derecha) ---
    RenderItem* paredX = new RenderItem(
        CreateShape(PxBoxGeometry(1000, 1000, 1)),
        new PxTransform(PxVec3(0, 0, -500)), Vector4(0.3f, 0.3f, 0.3f, 1.0f));

    RegisterRenderItem(paredX);
    _decoration.push_back(paredX);

    // --- Pared en eje Z (pared fondo) ---
    RenderItem* paredZ = new RenderItem(
        CreateShape(PxBoxGeometry(1, 1000, 1000)),
        new PxTransform(PxVec3(-500, 0, 0), PxQuat(PxPi / 2, PxVec3(1, 0, 0))),
        Vector4(0.3f, 0.3f, 0.3f, 1.0f));

    RegisterRenderItem(paredZ);
    _decoration.push_back(paredZ);


   /* 
    RenderItem* emisorV1 = new RenderItem(
        CreateShape(PxBoxGeometry(10, 1, 10)),
        new PxTransform(PxVec3(0, 0, 0)),
        Vector4(0.3f, 0.3f, 0.3f, 1.0f));

    RegisterRenderItem(emisorV1);

    _decoration.push_back(emisorV1);*/


    /*RenderItem* emisorV2 = new RenderItem(
        CreateShape(PxBoxGeometry(1000, 1, 1000)),
        new PxTransform(PxVec3(0, 0, 0)),
        Vector4(0.3f, 0.3f, 0.3f, 1.0f));

    RegisterRenderItem(emisorV2);

    _decoration.push_back(emisorV2);*/


        // Viento vertical
    _particleSystem->createWind(
        Vector3(0.0f, 30.0f, 0.0f),  
        Vector3(0, 0, 0),            
        Vector3(200, 2000, 200),        
        1.0f, 0.0f);

    // Gravedad 
    _particleSystem->createGravity();

    // Vientos laterales
    _particleSystem->createWind(Vector3(30, 0, 0), Vector3(0, 100, 0), Vector3(50, 50, 50), 0.5f);
    //_particleSystem->createWind(Vector3(-40, 0, 0), Vector3(0, 200, 0), Vector3(50, 50, 50), 0.5f);

    // Explosiones intermitentes
    //_particleSystem->createExplosion(Vector3(0, 150, 0), 400, 40, 2, 10);
    //_particleSystem->createExplosion(Vector3(0, 300, 0), 600, 50, 3, 20);

    //_particleSystem->createParticles();

    _cloudSystem = new CloudSystem(-50, 50, -100, -50);

}

void GameScene::update(double t)
{
	_particleSystem->update(t);
    _cloudSystem->update(t, _player->getTransform().p);
    if (!_player || !_particleSystem) return;

    // movimiento lateral
    const float moveSpeed = 100.0f;
    /*if (GetAsyncKeyState('A') & 0x8000)
        _player->addForce(Vector3(-moveSpeed, 0, 0));
    if (GetAsyncKeyState('D') & 0x8000)
        _player->addForce(Vector3(moveSpeed, 0, 0));*/

    // Limitar movimiento horizontal
    Vector3 pos = _player->getTransform().p;
    std::cout << "x: " << pos.x << " y: " << pos.y << " z: " << pos.z << "\n";
    /*RegisterRenderItem(new RenderItem(
        CreateShape(PxBoxGeometry(1, 1, 1)),
        new PxTransform(pos), Vector4(0.3f, 0.3f, 0.3f, 1.0f)));*/
    if (pos.x > 50) pos.x = 50;
    if (pos.x < -50) pos.x = -50;
    _player->setTransform(physx::PxTransform(pos));
    _cam->moveTo(_player->getTransform());

    _particleSystem->update(t);

}

void GameScene::render() const
{

}

void GameScene::exit()
{
    delete _particleSystem;
    _particleSystem = nullptr;
}

void GameScene::create()
{
    _particleSystem->createParticles();
}