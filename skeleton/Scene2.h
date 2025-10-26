#pragma once
#include "Scene.h"

class Bullet;
class Scene2 :
    public Scene
{
public:
	Scene2();
	~Scene2() override;

	void update(double t) override;
	void render() const override;
	void exit() override;
	void enter() override;

	void create() override;

protected:

	std::vector<Bullet*> _gObjects;
};

