#pragma once
#include "Scene.h"
#include <list>
#include <vector>

class ParticleSystem;
class Particle;
class RigidParticle;
class CloudSystem;
class WindForce;
class ExplosionsForce;
class GravityForce;
class WindLineGen;
class WindForceM;
class AnchoredSpringFG;
class RenderItem;
namespace Snippets { class Camera; }
class GameScene : public Scene
{
protected:
    struct WindGenData {
        WindForce* force;
        WindLineGen* gen;
        double timer;
        double interval;
    };

public:
    GameScene(Snippets::Camera* cam);
    ~GameScene() override;

    void update(double t) override;
    void render() const override;
    void exit() override;
    void enter() override;
    void toggleWind(int index);
    void keyPressed(unsigned char key) override;

protected:
    ParticleSystem* _particleSystem;
    RigidParticle* _player;

    Snippets::Camera*  _cam;

    std::list<RenderItem*> _decoration;
    CloudSystem* _cloudSystem;
    GravityForce* _gravity;
    std::list<RenderItem*> _windBoxes;       
    std::list<WindForce*> _windForces; 
    WindForce* _windUp; 
    std::list<WindForceM*> _windForcesM; 
    std::list<ExplosionsForce*> _explosions; 

    std::vector<RigidParticle*> _static_obstacles;    

    std::vector<RigidParticle*> _meteors;
    bool _meteorsGenerated;

    float _cameraY;
    float _cameraSpeed;

    float _win_mark;

    int _max_second;
    int _max_third;
};
