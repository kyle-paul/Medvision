#include "standard.h"
#include "exlibs.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

int main()
{
    GLFWwindow *window;
    if (!glfwInit())
    {
        cout << "Error initializing GLFW" << endl;
        return -1;
    }

    cout << "This is Medvision Version 0.1.0" << endl;
}