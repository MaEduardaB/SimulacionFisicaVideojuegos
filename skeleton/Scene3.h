#pragma once
#include "Scene.h"
class ParticleSystem;
class Scene3 :
    public Scene
{
public:
	Scene3();
	~Scene3() override;

	void update(double t) override;
	void render() const override;
	void exit() override;
	void enter() override;

	void create() override;

protected:
	ParticleSystem* _particleSystem;
};

