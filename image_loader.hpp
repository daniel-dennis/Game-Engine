// (c) Daniel Dennis 2018

// Loads and binds image using DevIL library
// Portions of this class use code from https://r3dux.org/tag/image/
// (accessed 26th November 2018)

#ifndef IMAGE_LOADER_HPP
#define IMAGE_LOADER_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

namespace dd
{
    class image_loader
    {
    private:
        GLuint load_image(const char* file_name);
        GLuint location;
    public:
        image_loader(const char* file_name);
        ~image_loader();

        GLuint get_location() { return location; }
    };
}

#endif