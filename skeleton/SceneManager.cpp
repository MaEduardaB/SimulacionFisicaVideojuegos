#include "SceneManager.h"
#include <iostream>

SceneManager::SceneManager() {}
SceneManager::~SceneManager()
{
    clear_scenes();
}

SceneManager& SceneManager::instance()
{
    static SceneManager inst;
    return inst;
}

void SceneManager::add_scene(Scene* s)
{
    if (s) _scenes.push_back(s);
}

void SceneManager::change_to_scene(SCENE_TYPE type)
{
    int idx = static_cast<int>(type);
    if (idx < 0 || idx >= _scenes.size()) return;

    if (_curr_scene != type)
        _scenes[static_cast<int>(_curr_scene)]->exit();

    _curr_scene = type;
    _scenes[idx]->enter();

    display_text = _scenes[idx]->get_display_text();
    //std::cout << "Cambiando a escena " << idx << "\n";
}

void SceneManager::update(double t)
{
    if (_scenes.empty()) return;
    int idx = static_cast<int>(_curr_scene);
    if (idx < 0 || idx >= _scenes.size()) return;
    _scenes[idx]->update(t);
}

void SceneManager::key_input(unsigned char key)
{
     if (_scenes.empty()) return;
    int idx = static_cast<int>(_curr_scene);
    if (idx < 0 || idx >= _scenes.size()) return;
    switch (key) {
        case '1':
            change_to_scene(SCENE_TYPE::SCENE1);
            return;
        case '2':
            change_to_scene(SCENE_TYPE::SCENE2);
            return;
        case '3':
            change_to_scene(SCENE_TYPE::SCENE3);
            return;
        case '4':
            change_to_scene(SCENE_TYPE::SCENE4);
            return;
        case '5':
            change_to_scene(SCENE_TYPE::SCENE5);
            return;
    }

    // Pasar input a la escena actual
    _scenes[idx]->keyPressed(key);
}

void SceneManager::clear_scenes()
{
   for (Scene* s : _scenes)
        delete s;
    _scenes.clear();
}

Scene* SceneManager::get_curr_scene()
{
    if (_scenes.empty()) return nullptr;
    int idx = static_cast<int>(_curr_scene);
    if (idx < 0 || idx >= _scenes.size()) return nullptr;
    return _scenes[idx];
}
