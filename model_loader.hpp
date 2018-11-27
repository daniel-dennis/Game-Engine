// (c) Daniel Dennis 2018

// Loads and binds vertices using Assimp library
// Portions of this class use code from sample code provided for this module
// on BlackBoard

#ifndef MODEL_LOADER_HPP
#define MODEL_LOADER_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace dd
{
    typedef struct
    {
        size_t mPointCount;
        std::vector<glm::vec3> mVertices;
        std::vector<glm::vec3> mNormals;
        std::vector<glm::vec2> mTextureCoords;
    } model_data_t;

    typedef struct
    {
        GLuint vertices_VBO;
        GLuint normals_VBO;
        GLuint texture_coord_VBO;
    } model_info_t;

    class model_loader
    {
    private:
        // Private variables
        model_data_t model_data;
        model_info_t model_info;

        // Private methods
        void load_mesh_internal(const char* file_name);
    public:
        // Publics mthods and constructors
        model_loader();
        ~model_loader();
        void load_mesh(const char* file_name);
        
        // Get methods
        GLuint  get_vertices_VBO()      { return model_info.vertices_VBO; }     
        GLuint  get_normals_VBO()       { return model_info.normals_VBO; }      
        GLuint  get_texture_coord_VBO() { return model_info.texture_coord_VBO; }                  
        GLsizei get_point_count()       { return model_data.mPointCount; }      
    };
}

#endif