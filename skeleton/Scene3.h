#pragma once
#include "Scene.h"
class ParticleSystem;
class Scene3 :
    public Scene
{
public:
	Scene3(Snippets::Camera* cam);
	~Scene3() override;

	void update(double t) override;
	void render() const override;
	void exit() override;
	void enter() override;

	void keyPressed(unsigned char key) override;

protected:
	Snippets::Camera* _cam
};

