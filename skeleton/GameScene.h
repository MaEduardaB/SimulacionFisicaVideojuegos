#pragma once
#include "Scene.h"
#include <list>

class ParticleSystem;
class Particle;
class CloudSystem;
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

	void create() override;

protected:
	ParticleSystem* _particleSystem;
	Particle* _player;

	Snippets::Camera*  _cam;

	std::list<RenderItem*> _decoration;
	CloudSystem* _cloudSystem;
};

