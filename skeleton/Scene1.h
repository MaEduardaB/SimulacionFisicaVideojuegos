#pragma once
#include "Scene.h"
#include <vector>

class Particle;
class Scene1 :
    public Scene
{
public:
	Scene1(Snippets::Camera* cam);
	~Scene1() override;

	void update(double t) override;
	void render() const override;
	void exit() override;
	void enter() override;

	void keyPressed(unsigned char key) override;

protected:
	Snippets::Camera* _cam;

	std::vector<Particle*> _gObjects;
};

