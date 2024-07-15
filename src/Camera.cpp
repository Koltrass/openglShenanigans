#include "Camera.h"
Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch)
{
	m_pos = pos;
	m_worldUp = up;
	m_yaw = yaw;
	m_pitch = pitch;
	updateCameraVectors();
}
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{
	m_pos = glm::vec3(posX, posY, posZ);
	m_worldUp = glm::vec3(upX, upY, upZ);
	m_yaw = yaw;
	m_pitch = pitch;
	updateCameraVectors();
}
Camera::Camera() 
{
	m_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_yaw = 0.0;
	m_pitch = 0.0;
	updateCameraVectors();
}

void Camera::processKeyboard(direction direction, float deltaTime)
{
	float velocity = m_movementSpeed * deltaTime;
	switch (direction)
	{
		case FORWARD:
		{
			m_pos += velocity * m_front;
			break;
		}
		case BACKWARD:
		{
			m_pos -= velocity * m_front;
			break;
		}
		case RIGHT:
		{
			m_pos += velocity * m_right;
			break;
		}
		case LEFT:
		{
			m_pos -= velocity * m_right;
			break;
		}
		case UP:
		{
			m_pos.y += velocity;
			break;
		}
		case DOWN:
		{
			m_pos.y -= velocity;
			break;
		}
	}
}
void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch)
{
	m_yaw += xOffset * m_mouseSensitivity;
	m_pitch += yOffset * m_mouseSensitivity;
	updateCameraVectors();
}
void Camera::processMouseScroll(float yOffset)
{
	m_zoom -= yOffset;
	if (m_zoom < 1.0f)
		m_zoom = 1.0f;
	else if (m_zoom > 45.0f)
		m_zoom = 45.0f;
}
glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(m_pos, m_pos + m_front, m_up);
}
float Camera::getZoom()
{
	return m_zoom;
}
void Camera::updateCameraVectors()
{
	m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front.y = sin(glm::radians(m_pitch));
	m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(m_front);

	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}