#pragma once
#include "Scene.h"
class ParticleSystem;
class GameScene :
    public Scene
{
public:
	GameScene();
	~GameScene() override;

	void update(double t) override;
	void render() const override;
	void exit() override;
	void enter() override;

	void create() override;

protected:
	ParticleSystem* _particleSystem;
};

