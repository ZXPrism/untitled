#pragma once

#include <glm/glm.hpp>

namespace core {

    class Camera
    {
    public:
        glm::vec3 _pos = {0.0f, 0.0f, 0.0f};
        glm::vec3 _front = {0.0f, 0.0f, -1.0f};
        glm::vec3 _worldUp = {0.0f, 1.0f, 0.0f};

        glm::mat4 _viewMatrix;
        glm::mat4 _projectionMatrix;

    public:
        void Perspective(float fov, float aspectRatio, float zNear, float zFar);
        void UpdateMatrices();

    private:
        bool _projMatrixUpdateFlag = false;
        float _fov;
        float _aspectRatio;
        float _zNear;
        float _zFar;
    };

} // namespace core
