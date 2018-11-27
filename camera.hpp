// (c) Daniel Dennis 2018

// Implements a camera class
// Parts of this code take inspiration from https://learnopengl.com
// (accessed 26th November 2018)


#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

namespace dd
{
    class camera
    {
    private:
        const int frame_width;
        const int frame_height;

        glm::vec3 cam_pos;        
        glm::vec3 cam_front;
        glm::vec3 cam_up;

        glm::mat4 view;

        int last_x;
        int last_y;

        float pitch;
        float yaw;    
    public:
        camera(int frame_width, int frame_height);
        ~camera();

        glm::mat4& get_view();
        void move_x(float magnitude);
        void move_y(float magnitude);

        void mouse_handler(float x_pos, float y_pos);
        glm::vec3& get_cam_position();
    };
}

#endif