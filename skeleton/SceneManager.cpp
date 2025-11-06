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

void SceneManager::change_to_scene(int idx)
{
    if (idx < 0 || idx >= _scenes.size()) return;

    if (_curr_scene != -1)
        _scenes[_curr_scene]->exit();

    _curr_scene = idx;
    _scenes[_curr_scene]->enter();

    display_text = _scenes[_curr_scene]->get_display_text();
    std::cout << "Cambiando a escena " << idx << "\n";
}

void SceneManager::update(double t)
{
    if (_curr_scene != -1 && _curr_scene < _scenes.size())
        _scenes[_curr_scene]->update(t);
}

void SceneManager::key_input(unsigned char key)
{
    if (_curr_scene == -1) return;

    // Cambiar de escena si es un número
    if (key >= '0' && key <= '9')
    {
        int idx = key - '0';
        change_to_scene(idx);
        return;
    }

    // Pasar input a la escena actual
    _scenes[_curr_scene]->keyPressed(key);
}

void SceneManager::clear_scenes()
{
   for (Scene* s : _scenes)
        delete s;
    _scenes.clear();
}

Scene* SceneManager::get_curr_scene()
{
    if (_curr_scene == -1 || _curr_scene >= _scenes.size()) return nullptr;
    return _scenes[_curr_scene];
}
