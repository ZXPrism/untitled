#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

namespace core {

    void Transform::UpdateModelMatrix()
    {
        constexpr glm::vec3 axisX{1.0f, 0.0f, 0.0f};
        constexpr glm::vec3 axisY{0.0f, 1.0f, 0.0f};
        constexpr glm::vec3 axisZ{0.0f, 0.0f, 1.0f};

        _modelMatrix = glm::mat4(1.0f);
        _modelMatrix = glm::translate(_modelMatrix, _pos); // trap..
        _modelMatrix = glm::rotate(_modelMatrix, _rotation.x, axisX);
        _modelMatrix = glm::rotate(_modelMatrix, _rotation.y, axisY);
        _modelMatrix = glm::rotate(_modelMatrix, _rotation.z, axisZ);
        _modelMatrix = glm::scale(_modelMatrix, _scale);
    }

} // namespace core
