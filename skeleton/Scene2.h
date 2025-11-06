#pragma once
#include "Scene.h"
#include <vector>
class Bullet;
class Scene2 :
    public Scene
{
public:
	Scene2(Snippets::Camera* cam);
	~Scene2() override;

	void update(double t) override;
	void render() const override;
	void exit() override;
	void enter() override;

	void keyPressed(unsigned char key) override;

protected:
	Snippets::Camera* _cam;

	std::vector<Bullet*> _gObjects;
};

