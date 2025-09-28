#pragma once

#include <vector>
#include <list>
#include "Scene.h"

class Particle;

class SceneManager
{

public:
	SceneManager();
	void update(double t);


protected:
	int _act;
	std::vector<Scene*> _scenes;
};

