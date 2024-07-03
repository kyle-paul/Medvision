#pragma once
#include "../exlibs.h"
#include "../renderer/shaders/shader.h"
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
    void setup_glfw();
    void setup_opengl();
    void setup_imgui();
};