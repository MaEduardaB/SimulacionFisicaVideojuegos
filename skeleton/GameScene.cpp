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
#include "WindLineGen.h"
#include "FogGen.h"
#include "CloudSystem.h"
#include "Particle.h"
#include "RigidParticle.h"
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
#include "SpringForceGenerator.h"
#include "BouyancyForceGenerator.h"
#include "AnchoredSpringFG.h"

#include "core.hpp"
#include "RenderUtils.hpp"


using namespace physx;

GameScene::GameScene(Camera* cam)  : _particleSystem(nullptr),
      _cloudSystem(nullptr),
      _cam(cam),
    _player(nullptr),
	_meteorsGenerated(false)
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

    delete _player;
    _player = nullptr;

    for (auto* rp : _meteors) {
        delete rp;
    }
    _meteors.clear();


    DeregisterAllRenderItem();
}
void GameScene::enter()
{
    //std::cout << "Iniciando GameScene\n";
    _force_registry = new ForceRegestry();
    _particleSystem = new ParticleSystem();

    RIGID_BODY_PROPS props;
    props._transform = Vector3(0.0, 10.0, 0.0);
    props._velocity = Vector3(0.0, 0.0f, 0.0);
    props.color = Vector4(1.0f, 0.41f, 0.71f, 1.0f);
    props._mass = 8.0;
    props._sizeX = 5;
    props._sizeY = 5;
    props._sizeZ = 5;
    props._lifeTime = 10000;
    props._shapeType = "SPHERE";
    props._isDynamic = true;

    _player = new RigidParticle(props);

    RenderItem* suelo = new RenderItem(
        CreateShape(PxBoxGeometry(1000, 1, 1000)),
        new PxTransform(PxVec3(0, 0, 0)),
        Vector4(0.4f, 0.8f, 0.4f, 1.0f));  
  
    RegisterRenderItem(suelo);
    _decoration.push_back(suelo);


    float cieloHeight = 5000.0f;
    float zCielo = -500.0f;

    RenderItem* paredCielo = new RenderItem(
        CreateShape(PxBoxGeometry(1200, cieloHeight / 2, 1)),
        new PxTransform(PxVec3(0, cieloHeight / 2, zCielo)),
        Vector4(0.3f, 0.5f, 0.8f, 1.0f)
    );
    RegisterRenderItem(paredCielo);
    _decoration.push_back(paredCielo);

    const int numLayers = 10; 
    float layerHeight = 200.0f; 
    float currentTop = cieloHeight;
    Vector4 colorFinal = Vector4(0.08f, 0.08f, 0.18f, 1.0f);

    for (int i = 0; i < numLayers; ++i)
    {
        float yCenter = currentTop + (layerHeight / 2);
        float t = i / (float)(numLayers - 1);

        Vector4 color;
        if (i == numLayers - 1) {
            color = colorFinal;
        }
        else {
            color = Vector4(
                0.3f * (1.0f - t),
                0.5f * (1.0f - t),
                0.8f * (1.0f - t) + 0.15f * t,
                1.0f
            );
        }

        float zOffset = zCielo + (i * 0.2f);

        RenderItem* layer = new RenderItem(
            CreateShape(PxBoxGeometry(1200, layerHeight / 2, 1)),
            new PxTransform(PxVec3(0, yCenter, zOffset)),
            color
        );
        RegisterRenderItem(layer);
        _decoration.push_back(layer);

        currentTop += layerHeight;
    }

    float espacioHeight = 10000.0f; 
    float zEspacio = zCielo + 5.0f;

    RenderItem* paredEspacio = new RenderItem(
        CreateShape(PxBoxGeometry(1200, espacioHeight / 2, 1)),
        new PxTransform(PxVec3(0, currentTop + (espacioHeight / 2), zEspacio)),
        colorFinal
    );
    RegisterRenderItem(paredEspacio);
    _decoration.push_back(paredEspacio);

    float anchoEspacio = 1200.0f;
    float alturaMin = cieloHeight + 200.0f;
    float alturaMax = currentTop + espacioHeight - 200.0f;
    float zEstrellas = -480.0f;
    int numEstrellas = 80; 

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < numEstrellas; ++i)
    {
        float x = (rand() / (float)RAND_MAX * anchoEspacio) - (anchoEspacio / 2);
        float y = alturaMin + (rand() / (float)RAND_MAX * (alturaMax - alturaMin));

        float tamBase = 2.0f + (rand() / (float)RAND_MAX * 6.0f);
        float radio = tamBase * 0.15f;
        float halfHeight = tamBase * 0.8f;

        float brillo = 0.8f + (rand() / (float)RAND_MAX * 0.4f);
        float azulado = 0.85f + (rand() / (float)RAND_MAX * 0.15f);
        Vector4 colorEstrella = Vector4(1.0f, 1.0f, azulado, brillo);

        // Primera capsula
        RenderItem* capsula1 = new RenderItem(
            CreateShape(PxCapsuleGeometry(radio, halfHeight)),
            new PxTransform(PxVec3(x, y, zEstrellas), PxQuat(0, PxVec3(0, 0, 1))),
            colorEstrella
        );
        RegisterRenderItem(capsula1);
        _decoration.push_back(capsula1);

        // Segunda capsula rotada
        RenderItem* capsula2 = new RenderItem(
            CreateShape(PxCapsuleGeometry(radio, halfHeight)),
            new PxTransform(PxVec3(x, y, zEstrellas + 0.02f),
                PxQuat(3.14159f / 3, PxVec3(0, 0, 1))),
            colorEstrella
        );
        RegisterRenderItem(capsula2);
        _decoration.push_back(capsula2);

        // Tercera capsula rotada
        RenderItem* capsula3 = new RenderItem(
            CreateShape(PxCapsuleGeometry(radio, halfHeight)),
            new PxTransform(PxVec3(x, y, zEstrellas + 0.04f),
                PxQuat(2 * 3.14159f / 3, PxVec3(0, 0, 1))),
            colorEstrella
        );
        RegisterRenderItem(capsula3);
        _decoration.push_back(capsula3);
    }

    _windUp = new WindForce(
        Vector3(0.0f, 1600.0f, 0.0f),
        Vector3(0, 0, 0),
        Vector3(2000, 30000, 2000),
        1.0f, 0.0f);

    _force_registry->add(_player, _windUp);


    _gravity = new GravityForce();
    _force_registry->add(_player, _gravity);
    _particleSystem->createGravity();

  
    std::vector<WindZone> zonas = {
        { Vector3(805, 0, 0), Vector3(-15, 200, 0), Vector3(40, 50, 15),
        Vector4(0.7f, 0.8f, 0.5f, 0.4f) },

        { Vector3(-800, 0, 0), Vector3(20, 800, 0), Vector3(35, 60, 15),
        Vector4(1.0f, 0.6f, 0.6f, 0.4f) },

        { Vector3(0, -600, 0), Vector3(-10, 1200, 0), Vector3(45, 70, 15),
        Vector4(0.6f, 0.7f, 1.0f, 0.4f) },

        { Vector3(-900, -300, 0), Vector3(15, 1600, 0), Vector3(50, 80, 15),
        Vector4(1.0f, 0.7f, 0.5f, 0.4f) },

        { Vector3(405, 0, 0), Vector3(-20, 4000, 0), Vector3(60, 90, 15),
        Vector4(0.5f, 0.9f, 0.7f, 0.4f) },

        { Vector3(-400, 20, 0), Vector3(25, 3000, 0), Vector3(65, 100, 15),
        Vector4(0.9f, 0.5f, 0.9f, 0.4f) },

        { Vector3(600, 0, 0), Vector3(-30, 7000, 0), Vector3(80, 120, 15),
        Vector4(1.0f, 0.4f, 0.4f, 0.5f) },

        { Vector3(-500, 0, 0), Vector3(35, 8000, 0), Vector3(85, 130, 15),
        Vector4(0.4f, 0.4f, 1.0f, 0.5f) },

        { Vector3(-500, 0, 0), Vector3(35, 8800, 0), Vector3(85, 80, 15),
        Vector4(0.4f, 0.4f, 1.0f, 0.5f) },

        // { Vector3(-400, 0, 0), Vector3(25, 9500, 0), Vector3(65, 70, 15),
        // Vector4(0.9f, 0.5f, 0.9f, 0.4f) },

        // { Vector3(-400, 0, 0), Vector3(25, 10000, 0), Vector3(65, 70, 15),
        // Vector4(0.9f, 0.5f, 0.9f, 0.4f) },

        // { Vector3(0, -1000, 0), Vector3(-30, 12000, 0), Vector3(80, 80, 15),
        // Vector4(1.0f, 0.4f, 0.4f, 0.5f) }
    };

    for (size_t i = 0; i < zonas.size(); ++i)
    {
        WindForce* wf = new WindForce(zonas[i].windVelocity, zonas[i].areaCenter,
            zonas[i].areaHalfSize, 0.6f);

        RenderItem* windBox = new RenderItem(
            CreateShape(PxBoxGeometry(zonas[i].areaHalfSize.x, zonas[i].areaHalfSize.y,
                zonas[i].areaHalfSize.z)),
            new PxTransform(PxVec3(zonas[i].areaCenter.x, zonas[i].areaCenter.y,
                zonas[i].areaCenter.z)),
            zonas[i].color
        );

        RegisterRenderItem(windBox);
        _windBoxes.push_back(windBox);
        _windForces.push_back(wf);
        _force_registry->add(_player, wf);

        // bool horizontal = std::abs(zonas[i].windVelocity.x) >= std::abs(zonas[i].windVelocity.y);

        // Vector3 start, end;
        // const Vector3& c = zonas[i].areaCenter;
        // const Vector3& h = zonas[i].areaHalfSize;

        // if (!horizontal)
        // {
        //     if (zonas[i].windVelocity.x > 0)
        //     {
        //         start = Vector3(c.x - h.x, c.y, c.z);
        //         end   = Vector3(c.x + h.x, c.y, c.z);
        //     }
        //     else
        //     {
        //         start = Vector3(c.x + h.x, c.y, c.z);
        //         end   = Vector3(c.x - h.x, c.y, c.z);
        //     }
        // }
        // else
        // {
        //     if (zonas[i].windVelocity.y > 0)
        //     {
        //         start = Vector3(c.x, c.y - h.y, c.z);
        //         end   = Vector3(c.x, c.y + h.y, c.z);
        //     }
        //     else
        //     {
        //         start = Vector3(c.x, c.y + h.y, c.z);
        //         end   = Vector3(c.x, c.y - h.y, c.z);
        //     }
        // }

        // WindLineGen* gen = new WindLineGen(std::mt19937(std::random_device{}()), start, end, zonas[i].windVelocity, 0.8, 5);
        // _windGens.push_back({wf, gen, 0.0, 1.0});
    }

    std::vector<Vector3> windVelocities = {
        Vector3(300,0,0), Vector3(-300,0,0),
        Vector3(400,0,0), Vector3(-400,0,0)
    };

    std::vector<Vector3> windCenters = {
        Vector3(0,1800,0), Vector3(40,5000,0),
        Vector3(-30,9000,0), Vector3(50,11000,0)
    };

    std::vector<Vector3> windSizes = {
        Vector3(25,60,15), Vector3(30,40,15),
        Vector3(35,30,15), Vector3(40,30,15)
    };

    for (size_t i = 0; i < 4; ++i)
    {
        WindForceM* wf = new WindForceM(windVelocities[i], windCenters[i], windSizes[i]);
        _windForcesM.push_back(wf);
        _force_registry->add(_player, wf);

        RenderItem* windBox = new RenderItem(
            CreateShape(PxBoxGeometry(windSizes[i].x, windSizes[i].y, windSizes[i].z)),
            new PxTransform(PxVec3(windCenters[i].x, windCenters[i].y, windCenters[i].z)),
            Vector4(0.5f, 0.7f, 0.9f, 0.3f)
        );
        RegisterRenderItem(windBox);
        _windBoxes.push_back(windBox);
    }

    // --- OBSTACULOS ESTATICOS ---    
    std::vector<Obstacle> obstacles = {
        { Vector3(-100, 300, 0), Vector3(100, 15, 10), Vector4(1.0f, 0.1f, 0.1f, 1.0f) },
        { Vector3(100, 450, 0), Vector3(80, 15, 10), Vector4(0.9f, 0.0f, 0.0f, 1.0f) },
        { Vector3(-100, 600, 0), Vector3(55, 15, 10), Vector4(0.8f, 0.1f, 0.1f, 1.0f) },

        { Vector3(50, 900, 0), Vector3(60, 15, 10), Vector4(1.0f, 0.2f, 0.2f, 1.0f) },
        { Vector3(-10, 1100, 0), Vector3(45, 15, 10), Vector4(0.9f, 0.15f, 0.15f, 1.0f) },
        { Vector3(20, 1400, 0), Vector3(40, 15, 10), Vector4(0.85f, 0.1f, 0.1f, 1.0f) },
        { Vector3(-30, 1700, 0), Vector3(55, 15, 10), Vector4(0.75f, 0.05f, 0.05f, 1.0f) },

        { Vector3(80, 2200, 0), Vector3(45, 15, 10), Vector4(1.0f, 0.0f, 0.0f, 1.0f) },
        { Vector3(-20, 2600, 0), Vector3(50, 15, 10), Vector4(0.9f, 0.05f, 0.05f, 1.0f) },
        { Vector3(80, 3000, 0), Vector3(35, 15, 10), Vector4(0.8f, 0.0f, 0.0f, 1.0f) },
        { Vector3(-30, 3300, 0), Vector3(55, 15, 10), Vector4(0.7f, 0.1f, 0.1f, 1.0f) },
        { Vector3(-20, 3800, 0), Vector3(50, 15, 10), Vector4(0.9f, 0.05f, 0.05f, 1.0f) },
        { Vector3(80, 4100, 0), Vector3(35, 15, 10), Vector4(0.8f, 0.0f, 0.0f, 1.0f) },
        { Vector3(-30, 4800, 0), Vector3(55, 15, 10), Vector4(0.7f, 0.1f, 0.1f, 1.0f) },

        { Vector3(20, 5800, 0), Vector3(60, 15, 10), Vector4(1.0f, 0.3f, 0.3f, 1.0f) },
        { Vector3(-20, 6100, 0), Vector3(65, 15, 10), Vector4(0.85f, 0.0f, 0.0f, 1.0f) },
        { Vector3(20, 7800, 0), Vector3(60, 15, 10), Vector4(1.0f, 0.3f, 0.3f, 1.0f) },
        { Vector3(-20, 8100, 0), Vector3(65, 15, 10), Vector4(0.85f, 0.0f, 0.0f, 1.0f) },
        { Vector3(10, 9300, 0), Vector3(70, 15, 10), Vector4(0.95f, 0.1f, 0.1f, 1.0f) }
    };

    for (const auto& obstacle : obstacles) {
        RIGID_BODY_PROPS props;
        props._transform = obstacle.position;
        props._velocity = Vector3(0, 0, 0);
        props.color = obstacle.color;
        props._mass = 0.0;
        props._sizeX = obstacle.size.x;
        props._sizeY = obstacle.size.y;
        props._sizeZ = obstacle.size.z;
        props._shapeType = "BOX";
        props._isDynamic = false;

        RigidParticle* obstacleParticle = new RigidParticle(props);
        _static_obstacles.push_back(obstacleParticle);
    }

    // --- MARCADOR DE FINAL ---
    _win_mark = 8000.0f;
    RenderItem* finalMarker = new RenderItem(
        CreateShape(PxBoxGeometry(1200, 0.5f, 1)),
        new PxTransform(PxVec3(0, _win_mark - 300, -480)),
        Vector4(11.0f, 0.0f, 0.0f, 1.0f)
    );

    RIGID_BODY_PROPS propAnchored;
    propAnchored._transform = Vector3(30.0, 800.0, 0.0);
    propAnchored._velocity = Vector3(0.0, 10.0f, 0.0);
    propAnchored.color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    propAnchored._mass = 8.0;
    propAnchored._sizeX = 5;
    propAnchored._sizeY = 5;
    propAnchored._sizeZ = 5;
    propAnchored._lifeTime = 10000;
    propAnchored._shapeType = "SPHERE";
    propAnchored._isDynamic = true;

    RigidParticle* p3 = new RigidParticle(propAnchored);
    AnchoredSpringFG* anchoredSpring = new AnchoredSpringFG(1, 10, Vector3(0,1000,0));
    _force_registry->add(p3, anchoredSpring);
    
    _cloudSystem = new CloudSystem(-150, 150, -250, -150);

    _max_second= 0;
    _max_third = 0;
}

void GameScene::update(double t)
{
	_particleSystem->update(t);
    _force_registry->updateForces();

    for(auto it = _meteors.begin(); it != _meteors.end(); ) {
        RigidParticle* rp = *it;
        rp->integrate(t);
        if(rp->getLifeTime() <= 0) {
            _force_registry->remove(rp, _gravity);
            delete rp;
            it = _meteors.erase(it);
        } else {
            ++it;
        }
    }

    _cloudSystem->update(t, _player->getPosition());
    Vector3 pos = _player->getPosition();
    // _static_obstacles.erase(
    //     std::remove_if(_static_obstacles.begin(), _static_obstacles.end(),
    //         [pos](RigidParticle* obs) {
    //             if (obs->getPosition().y < pos.y - 300.0f) {
    //                 delete obs;
    //                 return true;
    //             }
    //             return false;
    //         }),
    //     _static_obstacles.end());

  /*  auto itF = _windForces.begin();
    auto itB = _windBoxes.begin();

    while (itF != _windForces.end() && itB != _windBoxes.end()) {
        if ((*itF)->getAreaCenter().y < pos.y - 300.0f) {
            _force_registry->remove(_player, *itF);
            delete* itF;
            itF = _windForces.erase(itF);

            DeregisterRenderItem(*itB);
            delete* itB;
            itB = _windBoxes.erase(itB);
        }
        else {
            ++itF;
            ++itB;
        }
    }
*/

    if (!_player || !_particleSystem) return;

    // Limitar movimiento horizontal
    std::cout << "x: " << pos.x << " y: " << pos.y << " z: " << pos.z << "\n";

    if (pos.x < LeftLimit || pos.x > RightLimit)
    {
        SceneManager::instance().change_to_scene(SCENE_TYPE::GAME_OVER);
        return;
    }

    if(pos.y > 1800 && _max_second < 3){
         RIGID_BODY_PROPS propAnchored;
        propAnchored._transform = Vector3(60.0, 1900.0, 0.0);
        propAnchored._velocity = Vector3(0.0, 10.0f, 0.0);
        propAnchored.color = Vector4(1.0f, 1.0f, 0.71f, 1.0f);
        propAnchored._mass = 8.0;
        propAnchored._sizeX = 6;
        propAnchored._sizeY = 6;
        propAnchored._sizeZ = 6;
        propAnchored._lifeTime = 10000;
        propAnchored._shapeType = "SPHERE";
        propAnchored._isDynamic = true;

        RigidParticle* p4 = new RigidParticle(propAnchored);
        AnchoredSpringFG* anchoredSpring2 = new AnchoredSpringFG(1, 20, Vector3(0,2000,0));
        _force_registry->add(p4, anchoredSpring2);
        
       ++_max_second;
    }
    if(pos.y > 7880 && _max_third < 3){
         RIGID_BODY_PROPS propAnchored;
        propAnchored._transform = Vector3(-30.0, 7950.0, 0.0);
        propAnchored._velocity = Vector3(0.0, 10.0f, 0.0);
        propAnchored.color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
        propAnchored._mass = 8.0;
        propAnchored._sizeX = 10;
        propAnchored._sizeY = 10;
        propAnchored._sizeZ = 10;
        propAnchored._lifeTime = 10000;
        propAnchored._shapeType = "SPHERE";
        propAnchored._isDynamic = true;
        RigidParticle* p5 = new RigidParticle(propAnchored);
        AnchoredSpringFG* anchoredSpring3 = new AnchoredSpringFG(1, 15, Vector3(0,8000,0));
        _force_registry->add(p5, anchoredSpring3);

        ++_max_third;
    }

    if (pos.y >= _win_mark)
    {
        SceneManager::instance().change_to_scene(SCENE_TYPE::WIN);
        return;
    }

    if (pos.y < _cameraY - 400.0f)
    {
        SceneManager::instance().change_to_scene(SCENE_TYPE::GAME_OVER);
        return;
    }

    if (pos.y > 6000 && !_meteorsGenerated) {
        _meteorsGenerated = true;
        for(int i = 0; i < 10; i++) {
            RIGID_BODY_PROPS props;
            props._transform = Vector3(rand() % 200 - 100, pos.y + 100 + rand() % 100, rand() % 200 - 100);
            props._velocity = Vector3(rand() % 20 - 10, -50 - rand() % 50, rand() % 20 - 10);
            props.color = Vector4(0.8f, 0.2f, 0.1f, 1.0f);
            props._mass = 5.0 + rand() % 10;
            props._sizeX = 2 + rand() % 3;
            props._sizeY = 2 + rand() % 3;
            props._sizeZ = 2 + rand() % 3;
            props._lifeTime = 20.0;
            props._shapeType = "SPHERE";
            props._isDynamic = true;
            props._inertia = Vector3(1 + rand() % 5, 1 + rand() % 5, 1 + rand() % 5);
            RigidParticle* rp = new RigidParticle(props);
            _meteors.push_back(rp);
            _force_registry->add(rp, _gravity);
        }
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
    
   

    _particleSystem->update(t);

    // for (auto& wg : _windGens) {
    //     wg.timer += t;
    //     if (wg.timer >= wg.interval) {
    //         wg.timer = 0.0;
    //         auto particles = wg.gen->generateP();
    //         for (auto p : particles) {
    //             _particleSystem->addParticle(p);
    //             _force_registry->add(p, wg.force);
    //         }
    //     }
    // }

    _cam->moveTo(_player->getRigidBody()->getGlobalPose(), true);
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


    for (auto* rp : _meteors) {
        delete rp;
    }
    _meteors.clear();
    _meteorsGenerated = false;

    for (auto* deco : _decoration)
        DeregisterRenderItem(deco);

        _decoration.clear();

    delete _player;
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
                Vector3 playerPos = _player->getRigidBody()->getGlobalPose().p;
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