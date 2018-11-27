// (c) Daniel Dennis 2018

// Makes multiple instances of hierarchy class of type gl_object and packet_t
// to message individual nodes.
// Everything in this class is my own work

#ifndef HIERARCHY_IMPLEMENTATION_HPP
#define HIERARCHY_IMPLEMENTATION_HPP

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "hierarchy.hpp"
#include "gl_object.hpp"

namespace dd
{
    class hierarchy_implementation
    {
    private:
    // General variables
        int num_models;
    public:
        std::vector<hierarchy<gl_object, packet_t>* > objects;  // should be fixed, made protected?
        hierarchy_implementation(const char* file_path);
        ~hierarchy_implementation();
        void render_all_models();
        void change_camera(glm::mat4& camera);
        void change_view(glm::mat4& view);

        void change_viewer_pos(glm::vec3& data);
        void change_light_pos(glm::vec3& data);
    };
}

#endif