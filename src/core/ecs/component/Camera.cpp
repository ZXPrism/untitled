#include "Camera.h"

#include "core/Logger.h"

#include <glm/gtc/matrix_transform.hpp>

namespace core {

    void Camera::UpdateMatrices()
    {
        if (!_projMatrixUpdateFlag)
        {
            _projectionMatrix = glm::perspective(_fov, _aspectRatio, _zNear, _zFar);
            _projMatrixUpdateFlag = true;
        }

        _viewMatrix = glm::lookAt(_pos, _pos + _front, _worldUp);
    }

    void Camera::Perspective(float fov, float aspectRatio, float zNear, float zFar)
    {
        _fov = fov;
        _aspectRatio = aspectRatio;
        _zNear = zNear;
        _zFar = zFar;

        _projMatrixUpdateFlag = false;
    }

} // namespace core
