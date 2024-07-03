#pragma once
#include "../exlibs.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class App
{
public:
    App();
    ~App();
    void run();

private:
    GLFWwindow *window;
    bool show_imgui;
    ImVec4 clear_color;
    void setup_glfw();
    void setup_opengl();
    void setup_imgui();
};