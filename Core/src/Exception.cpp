#include "Exception.h"

#include <GL/glew.h>


void checkOpenGLError(const std::string& location, int line) 
{
    GLenum error = glGetError();

    while (error != GL_NO_ERROR) {
        std::string errorMessage;

        switch (error) {
        case GL_INVALID_ENUM:                  errorMessage = "GL_INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                 errorMessage = "GL_INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:             errorMessage = "GL_INVALID_OPERATION"; break;
        case GL_STACK_OVERFLOW:                errorMessage = "GL_STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW:               errorMessage = "GL_STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:                 errorMessage = "GL_OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: errorMessage = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
        default:                               errorMessage = "Unknown OpenGL error"; break;
        }

        // Add location and line to the error message
        throw OpenGLException(location + " - " + errorMessage + " at line " + std::to_string(line));
    }
}