#include "LowRenderer/Camera.h"

Camera::Camera(Vector3 position, Vector3 up, float yaw, float pitch)
    : Front(Vector3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) 
    : Front(Vector3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = Vector3(posX, posY, posZ);
    WorldUp = Vector3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Matrix4x4 Camera::GetViewMatrix()
{
    return Matrix4x4::ViewMatrix(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position = Position + Front * velocity;
    if (direction == BACKWARD)
        Position = Position - Front * velocity;
    if (direction == LEFT)
        Position = Position - Right * velocity;
    if (direction == RIGHT)
        Position = Position + Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    Vector3 front;
    front.x = cos(Yaw * ToRadians) * cos(Pitch * ToRadians);
    front.y = sin(Pitch * ToRadians);
    front.z = sin(Yaw * ToRadians) * cos(Pitch * ToRadians);
    Front = front.Normalized();
    Right = Front.CrossProduct(WorldUp).Normalized();
    Up = Right.CrossProduct(Front).Normalized();
}