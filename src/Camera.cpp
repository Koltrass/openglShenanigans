#include "Camera.h"
Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch) : position(pos), worldUp(up), yaw(yaw), pitch(pitch)
{
	movementSpeed = 4.0f;
	mouseSensitivity = 0.15f;
	zoom = 45.0f;
	updateCameraVectors();
}
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Camera(glm::vec3(posX, posY, posZ), glm::vec3(upX, upY, upZ), yaw, pitch) {}
Camera::Camera() : Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f) {}

void Camera::processKeyboard(direction direction, float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	switch (direction)
	{
		case FORWARD:
		{
			position += velocity * front;
			break;
		}
		case BACKWARD:
		{
			position -= velocity * front;
			break;
		}
		case RIGHT:
		{
			position += velocity * right;
			break;
		}
		case LEFT:
		{
			position -= velocity * right;
			break;
		}
		case UP:
		{
			position.y += velocity;
			break;
		}
		case DOWN:
		{
			position.y -= velocity;
			break;
		}
	}
}
void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch)
{
	yaw += xOffset * mouseSensitivity;
	pitch += yOffset * mouseSensitivity;
	if (pitch > 89.9f)
		pitch = 89.9f;
	else if (pitch < -89.9f)
		pitch = -89.9f;
	updateCameraVectors();
}
void Camera::processMouseScroll(float yOffset)
{
	zoom -= yOffset;
	if (zoom < 1.0f)
		zoom = 1.0f;
	else if (zoom > 45.0f)
		zoom = 45.0f;
}
glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}
float Camera::getZoom()
{
	return zoom;
}
glm::vec3 Camera::getPosition()
{
	return position;
}
glm::vec3 Camera::getDirection()
{
	return front;
}
void Camera::lookAlongVector(glm::vec3 vector)
{
	updateCameraVectors(vector);
	return;
}
void Camera::updateCameraVectors(glm::vec3 direction)
{
	glm::vec3 temp = glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));
	if (direction.x != 0.0f || direction.z != 0.0f)
	{
		front = glm::normalize(direction);
		yaw = glm::degrees(acos(temp.x)) * ((temp.z < 0.0f) ? -1.0f : 1.0f);
		pitch = glm::degrees(asin(front.y));
		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));
	}
	else
	{
		pitch = glm::degrees(asin(normalize(direction).y));
		if (pitch > 89.9f)
			pitch = 89.9f;
		else if (pitch < -89.9f)
			pitch = -89.9f;
		updateCameraVectors();
	}
}
void Camera::updateCameraVectors()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}