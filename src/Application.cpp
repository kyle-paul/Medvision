#include <iostream>
#include "GLFW/glfw3.h"
using namespace std;

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