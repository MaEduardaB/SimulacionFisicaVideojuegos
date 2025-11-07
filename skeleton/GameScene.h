#pragma once
#include "Scene.h"
#include <list>

class ParticleSystem;
class Particle;
class CloudSystem;
class WindForce;
class ExplosionsForce;
class GravityForce;
class WindForceM;
class RenderItem;
namespace Snippets { class Camera; }
class GameScene :
    public Scene
{
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
	Particle* _player;

	Snippets::Camera*  _cam;

	std::list<RenderItem*> _decoration;
	CloudSystem* _cloudSystem;
	GravityForce* _gravity;
	std::list<RenderItem*> _windBoxes;       
	std::list<WindForce*> _windForces; 
	WindForce* _windUp; 
	std::list<WindForceM*> _windForcesM; 
	std::list<ExplosionsForce*> _explosions; 
};