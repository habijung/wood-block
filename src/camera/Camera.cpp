#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up)
{
    mPosition = position;
    mFront = front;
    mUp = up;
    mSpeed = 2.5f;
    mZoom = 45.0f;
}

Camera::~Camera() {}

glm::mat4 Camera::getViewMatrix() { return glm::lookAt(mPosition, mPosition + mFront, mUp); }

float Camera::getZoom() { return mZoom; }

void Camera::processKeyboard(CameraMovement direction, float delta_time)
{
    float velocity = mSpeed * delta_time;

    if (direction == FORWARD)
    {
        mPosition += mFront * velocity;
    }
    if (direction == BACKWARD)
    {
        mPosition -= mFront * velocity;
    }
    if (direction == LEFT)
    {
        mPosition -= glm::normalize(glm::cross(mFront, mUp)) * velocity;
    }
    if (direction == RIGHT)
    {
        mPosition += glm::normalize(glm::cross(mFront, mUp)) * velocity;
    }
    if (direction == UP)
    {
        mPosition += mUp * velocity;
    }
    if (direction == DOWN)
    {
        mPosition -= mUp * velocity;
    }
}

void Camera::processMouseScroll(float offset_y)
{
    mZoom -= offset_y * mSpeed;

    if (mZoom < 15.0f)
    {
        mZoom = 15.0f;
    }
    if (mZoom > 60.0f)
    {
        mZoom = 60.0f;
    }
}
