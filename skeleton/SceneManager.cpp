#include "SceneManager.h"
#include "Scene1.h"


SceneManager::SceneManager()
{
}

void SceneManager::update(double t)
{
	_scenes[_act]->update(t);
}


