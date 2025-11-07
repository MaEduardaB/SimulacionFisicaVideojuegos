#include <fstream>
#include <PxPhysicsAPI.h>
#include <iostream>

#include "GameScene.h"
#include "ParticleSystem.h"
#include "GaussianGen.h"
#include "UniformGen.h"
#include "ParticleGen.h"
#include "FireworkGen.h"
#include "Constants.h"
#include "RainGen.h"
#include "FogGen.h"
#include "CloudSystem.h"
#include "Particle.h"
#include "GravityForce.h"
#include "ForceRegestry.h"
#include "WindForce.h"
#include "WindForceM.h"
#include "SceneManager.h"
#include "FireworkGen.h"
#include "ExplosionsForce.h"
#include "TorbellinoForce.h"
#include "Render/Camera.h"
#include "Render/Render.h"

#include "core.hpp"
#include "RenderUtils.hpp"



using namespace physx;

GameScene::GameScene(Camera* cam)  : _particleSystem(nullptr),
      _cloudSystem(nullptr),
      _cam(cam),
    _player(nullptr)
{
	display_text = "GameScene";

    _force_registry = nullptr;
}

GameScene::~GameScene()
{
	 for (auto* ps : _particleSystems)
        delete ps;
    _particleSystems.clear();

    delete _cloudSystem;
    _cloudSystem = nullptr;
}

void GameScene::enter()
{
    //std::cout << "Iniciando GameScene\n";
    _force_registry = new ForceRegestry();
    _particleSystem = new ParticleSystem();

    _cam->setDir(physx::PxVec3(-0.6f,-0.2f,-0.7f));
	_cam->setEye(physx::PxVec3(50.0f, 50.0f, 50.0f));

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

    const char* filename = "../assets/grass.jpg";

    std::ifstream test(filename);
    if (test.is_open()) {
        std::cout << "[OK] Archivo encontrado: ../assets/grass.png\n";
    } else {
        std::cout << "[ERROR] No se encontró el archivo: ../assets/grass.png\n";
    }
    test.close();

    // --- Cargar texturas ---
    // GLuint texGrass = LoadTexture(filename);
    // GLuint texSky = LoadTexture("../assets/sky.png");
    
    // --- Suelo ---
    RenderItem* suelo = new RenderItem(
        CreateShape(PxBoxGeometry(1000, 1, 1000)),
        new PxTransform(PxVec3(0, 0, 0)),
        Vector4(0.4f, 0.8f, 0.4f, 1.0f));  
    //suelo->textureID = texGrass;
    RegisterRenderItem(suelo);
    _decoration.push_back(suelo);

    // --- Pared con textura de cielo ---
    RenderItem* paredX = new RenderItem(
        CreateShape(PxBoxGeometry(1000, 1900, 1)),
        new PxTransform(PxVec3(0, 500, -500)),
        Vector4(0.4f, 0.6f, 0.9f, 1.0f));
    //paredX->textureID = texSky;
    RegisterRenderItem(paredX);
    _decoration.push_back(paredX);

    RenderItem* paredZ = new RenderItem(
        CreateShape(PxBoxGeometry(1, 1900, 1000)),
        new PxTransform(PxVec3(-500, 500, 0), PxQuat(PxPi / 2, PxVec3(1, 0, 0))),
        Vector4(0.4f, 0.6f, 0.9f, 1.0f));
    //paredZ->textureID = texSky;
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
    // _particleSystem->createWind(
    //     Vector3(0.0f, 150.0f, 0.0f),  
    //     Vector3(0, 1000, 0),            
    //     Vector3(2000, 20000, 2000),        
    //     1.0f, 0.0f);
    
    _windUp = new WindForce(
        Vector3(0.0f, 400.0f, 0.0f),  
        Vector3(0, 0, 0),            
        Vector3(2000, 20000, 2000),        
        1.0f, 0.0f);

    _force_registry->add(_player, _windUp);

    // Gravedad 
    _gravity = new GravityForce();
    _force_registry->add(_player, _gravity);
    _particleSystem->createGravity();

    // Vientos laterales
    
    struct WindZone {
        Vector3 windVelocity;
        Vector3 areaCenter;
        Vector3 areaHalfSize;
        Vector4 color;
    };

    std::vector<WindZone> zonas = {
        { Vector3(20, 0, 0), Vector3(-10, 300, 0), Vector3(30, 10, 10),
        Vector4(0.7f, 0.8f, 0.5f, 0.5f) },

        { Vector3(-20, 0, 0), Vector3(20, 500, 0), Vector3(40, 20, 10),
        Vector4(1.0f, 0.6f, 0.6f, 0.5f) },

        
        { Vector3(40, 0, 0), Vector3(0, 900, 0), Vector3(70, 20, 10),
        Vector4(0.6f, 1.0f, 0.7f, 0.5f) },

        { Vector3(-120, 0, 0), Vector3(10, 1100, 0), Vector3(80, 30, 10),
        Vector4(0.8f, 0.7f, 1.0f, 0.2f) }
    };

    for (size_t i = 0; i < zonas.size(); ++i)
    {
        WindForce* wf = new WindForce(zonas[i].windVelocity, zonas[i].areaCenter, zonas[i].areaHalfSize, 0.5f);
    
        RenderItem* windBox = new RenderItem(
            CreateShape(PxBoxGeometry(zonas[i].areaHalfSize.x, zonas[i].areaHalfSize.y, zonas[i].areaHalfSize.z)),
            new PxTransform(PxVec3(zonas[i].areaCenter.x, zonas[i].areaCenter.y, zonas[i].areaCenter.z)),
            zonas[i].color
        );

        RegisterRenderItem(windBox);

        _windBoxes.push_back(windBox);
        _windForces.push_back(wf); 
        _force_registry->add(_player, wf);
    }

    std::vector<Vector3> windVelocities = { Vector3(40,0,0), Vector3(-40,0,0) };
    std::vector<Vector3> windCenters = { Vector3(0,200,0), Vector3(50,300,0) };
    std::vector<Vector3> windSizes = { Vector3(15,15,15), Vector3(17,15,15) };

    for (size_t i = 0; i < 2; ++i)
    {
        WindForceM* wf = new WindForceM(windVelocities[i], windCenters[i], windSizes[i]);
        _windForcesM.push_back(wf);
        _force_registry->add(_player, wf);

        RenderItem* windBox = new RenderItem(
            CreateShape(PxBoxGeometry(windSizes[i].x, windSizes[i].y, windSizes[i].z)),
            new PxTransform(PxVec3(windCenters[i].x, windCenters[i].y, windCenters[i].z)),
            Vector4(0.5f,0.7f,0.9f,0.5f)
        );
        RegisterRenderItem(windBox);
        _windBoxes.push_back(windBox);
    }


    //_particleSystem->createExplosion(Vector3(0, 150, 0), 400, 40, 2, 10);
    //_particleSystem->createExplosion(Vector3(0, 300, 0), 600, 50, 3, 20);

    //_particleSystem->createParticles();

    _cloudSystem = new CloudSystem(-50, 50, -200, -150);

}

void GameScene::update(double t)
{
	_particleSystem->update(t);
    _force_registry->updateForces();
    _cloudSystem->update(t, _player->getTransform().p);
    if (!_player || !_particleSystem) return;

    // Limitar movimiento horizontal
    Vector3 pos = _player->getTransform().p;
    std::cout << "x: " << pos.x << " y: " << pos.y << " z: " << pos.z << "\n";

    if (pos.x < LeftLimit || pos.x > RightLimit)
    {
        SceneManager::instance().change_to_scene(SCENE_TYPE::GAME_OVER);
        return;
    }

    if (pos.y >= 1600.0f)
    {
        SceneManager::instance().change_to_scene(SCENE_TYPE::WIN);
        return;
    }

    // --- Actualizar explosiones ---
    for (auto it = _explosions.begin(); it != _explosions.end(); )
    {
        ExplosionsForce* ex = *it;
        ex->updateTime(static_cast<float>(t));

        if (ex->hasFaded())
        {
            _force_registry->remove(_player, ex);
            delete ex;
            it = _explosions.erase(it);
        }
        else
        {
            ++it;
        }
    }
    /*RegisterRenderItem(new RenderItem(
        CreateShape(PxBoxGeometry(1, 1, 1)),
        new PxTransform(pos), Vector4(0.3f, 0.3f, 0.3f, 1.0f)));*/
    // if (pos.x > 50) pos.x = 50;
    // if (pos.x < -50) pos.x = -50;
    _player->setTransform(physx::PxTransform(pos));
    _cam->moveTo(_player->getTransform(), true);

    _particleSystem->update(t);
}

void GameScene::render() const
{

}

void GameScene::exit()
{

    if (_particleSystem) {
        delete _particleSystem;
        _particleSystem = nullptr;
    }

    if (_cloudSystem) {
        delete _cloudSystem;
        _cloudSystem = nullptr;
    }

    for (auto* ps : _particleSystems)
        delete ps;
    _particleSystems.clear();
    
    for (auto* wf : _windForces)
        delete wf;
    _windForces.clear();

    for (auto* box : _windBoxes)
        DeregisterRenderItem(box);
    _windBoxes.clear();

    for (auto* wf : _windForcesM) delete wf;
    _windForcesM.clear();

    for (auto* ef : _explosions) delete ef;
    _explosions.clear();


    for (auto* deco : _decoration)
        DeregisterRenderItem(deco);

        _decoration.clear();

    _player = nullptr;

    DeregisterAllRenderItem();
}

void GameScene::toggleWind(int index)
{
    if (index < 0 || index >= _windForces.size()) return;

    auto itForce = _windForces.begin();
    auto itBox = _windBoxes.begin();
    std::advance(itForce, index);
    std::advance(itBox, index);

    WindForce* wf = *itForce;
    RenderItem* box = *itBox;

    bool active = !wf->isActive();
    wf->setActive(active);
    box->setVisible(active);
}


void GameScene::keyPressed(unsigned char key)
{
    if(key == 'G' || key == 'g') {
		SceneManager::instance().change_to_scene(SCENE_TYPE::MAIN_MENU);
	}

    const float lateralForce = 100.0f;
    switch (key)
    {
       case 'A':
        case 'a':
            _player->addForce(Vector3(-lateralForce, 0.0f, 0.0f));
            break;

        case 'D':
        case 'd':
            _player->addForce(Vector3(lateralForce, 0.0f, 0.0f));
            break;

        case 'W':
        case 'w':
            toggleWind(0);
            break;

        case 'E':
        case 'e':
            toggleWind(1);
            break;

        case 'R':
        case 'r':
            toggleWind(2);
            break;

        case 'T':
        case 't':
            toggleWind(3);
            break;
        case 'Y':
        case 'y':
            {
                Vector3 playerPos = _player->getTransform().p;
                Vector3 explosionPos = playerPos + Vector3(-20.0f, 0.0f, 0.0f); 
                FireworkGen* fg = new FireworkGen(std::mt19937(std::random_device{}()), Vector3(0, 0, 0), Vector3(0, 0, 0), 1.0, 1.0, 20);
                ExplosionsForce* newExplosion = new ExplosionsForce(explosionPos, 40.0f, 50.0f, 2.0f, 10.0f);
                _particleSystem->addGenerator(fg);
                _particleSystem->createParticles();
                _explosions.push_back(newExplosion);
                _force_registry->add(_player, newExplosion);
            }
            break;
        default:
            break;
    
    }
}