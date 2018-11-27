// (c) Daniel Dennis 2018

#include "camera.hpp"

namespace dd
{
    camera::camera(int frame_width, int frame_height) 
    : frame_width(frame_width), frame_height(frame_height)
    {
        cam_pos   = glm::vec3(15.0f, 15.0f,  3.0f);
        cam_front = glm::vec3(0.0f, 0.0f, -1.0f);
        cam_up    = glm::vec3(0.0f, 1.0f,  0.0f);

        last_x = frame_width / 2;
        last_y = frame_height / 2;
    }

    camera::~camera()
    {

    }

    glm::mat4& camera::get_view()
    {
        view = glm::lookAt(cam_pos, cam_pos + cam_front, cam_up);
        return view;
    }

    void camera::move_x(float magnitude)
    {
        cam_pos += magnitude * cam_front;
    }

    void camera::move_y(float magnitude)
    {
        cam_pos += glm::normalize(glm::cross(cam_front, cam_up)) * magnitude;
    }

    void camera::mouse_handler(float x_pos, float y_pos)
    {
        float xoffset = x_pos - last_x;
        float yoffset = last_y - y_pos;
        last_x = x_pos;
        last_y = y_pos;

        float sensitivity = 0.15f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;
        if(pitch > 89.0f)   pitch = 89.0f;
        if(pitch < -89.0f)  pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cam_front = glm::normalize(front);
    }

    glm::vec3& camera::get_cam_position()
    {
        return cam_pos;
    }
}