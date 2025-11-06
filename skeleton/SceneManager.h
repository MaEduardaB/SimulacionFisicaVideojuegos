#pragma once
#include <vector>
#include <string>
#include "Scene.h"

class SceneManager
{
public:
    static SceneManager& instance();

    void add_scene(Scene* s);
    void change_to_scene(int idx);
    void update(double t);
    void key_input(unsigned char key);
    void clear_scenes();

    void set_current_scene(int idx) { _curr_scene = idx; }
    Scene* get_curr_scene();
    std::string get_display_text() const { return display_text; }

private:
    SceneManager();
    ~SceneManager();

    std::vector<Scene*> _scenes;
    int _curr_scene = -1;

    std::string display_text = " ";
};
