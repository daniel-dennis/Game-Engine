// (c) Daniel Dennis 2018

// Loads and compiles vertix and fragment shader
// Portions of this class use code from https://github.com/SonarSystems/Modern-OpenGL-Tutorials
// (accessed 26th November 2018)

#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

namespace dd
{
    class shader_loader
    {
    public:
        GLuint program;
        shader_loader(const GLchar *vertexPath, const GLchar *fragmentPath);
        void use();
    };
}

#endif