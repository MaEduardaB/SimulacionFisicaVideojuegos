#pragma once
#include <vector>
#include <string>
#include "Scene.h"
#include "Constants.h"

class SceneManager
{
public:
    static SceneManager& instance();

    void add_scene(Scene* s);
    void change_to_scene(SCENE_TYPE type);
    void update(double t);
    void key_input(unsigned char key);
    void clear_scenes();

    Scene* get_curr_scene();
    std::string get_display_text() const { return display_text; }

private:
    SceneManager();
    ~SceneManager();

    std::vector<Scene*> _scenes;
    SCENE_TYPE _curr_scene = SCENE_TYPE::MAIN_MENU;

    std::string display_text = " ";
};
