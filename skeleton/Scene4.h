#pragma once
#include "Scene.h"
class ParticleSystem;
class Scene4 :
    public Scene
{
public:
	Scene4();
	~Scene4() override;

	void update(double t) override;
	void render() const override;
	void exit() override;
	void enter() override;

	void keyPressed(unsigned char key) override;

protected:
	ParticleSystem* _particleSystem;
};

