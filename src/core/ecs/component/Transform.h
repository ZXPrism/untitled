#pragma once

#include <glm/glm.hpp>

namespace core {

    class Transform
    {
    public:
        glm::vec3 _pos = {0.0f, 0.0f, 0.0f};
        glm::vec3 _rotation = {0.0f, 0.0f, 0.0f};
        glm::vec3 _scale = {1.0f, 1.0f, 1.0f};

        glm::mat4 _modelMatrix;

    public:
        void UpdateModelMatrix();
    };

} // namespace core
