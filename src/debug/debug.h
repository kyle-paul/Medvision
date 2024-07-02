#pragma once
#include "../config.h"
#include <assert.h>
#include <stdint.h>

#define ASSERT(x) \
    if (!(x))     \
    assert(false)
#define INT2VOIDP(i) (void *)(uintptr_t)(i)

void inline GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

bool inline GLCheckError()
{
    while (GLenum error = glGetError())
    {

        cout << "[OpenGL Error] ";
        switch (error)
        {
        case GL_INVALID_ENUM:
            cout << "GL_INVALID_ENUM : An unacceptable value is specified for an enumerated argument.";
            break;
        case GL_INVALID_VALUE:
            cout << "GL_INVALID_OPERATION : A numeric argument is out of range.";
            break;
        case GL_INVALID_OPERATION:
            cout << "GL_INVALID_OPERATION : The specified operation is not allowed in the current state.";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            cout << "GL_INVALID_FRAMEBUFFER_OPERATION : The framebuffer object is not complete.";
            break;
        case GL_OUT_OF_MEMORY:
            cout << "GL_OUT_OF_MEMORY : There is not enough memory left to execute the command.";
            break;
        case GL_STACK_UNDERFLOW:
            cout << "GL_STACK_UNDERFLOW : An attempt has been made to perform an operation that would cause an internal stack to underflow.";
            break;
        case GL_STACK_OVERFLOW:
            cout << "GL_STACK_OVERFLOW : An attempt has been made to perform an operation that would cause an internal stack to overflow.";
            break;
        default:
            cout << "Unrecognized error" << error;
        }
        cout << endl;
        return false;
    }
    return true;
}

#ifdef DEBUG
#define GLCall(x)   \
    GLClearError(); \
    x;              \
    ASSERT(GLCheckError())
#else
#define GLCall(x) x
#endif