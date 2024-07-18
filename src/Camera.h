#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum direction
{
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT,
	UP,
	DOWN
};
class Camera
{
private:
	glm::vec3 m_pos;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	float m_yaw;
	float m_pitch;

	float m_movementSpeed;
	float m_mouseSensitivity;
	float m_zoom;
public:
	Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	Camera();

	void processKeyboard(direction SomeParam,float deltaTime);
	void processMouseMovement(float xOffset, float yOffset, bool constrainPitch);
	void processMouseScroll(float zoomOffset);

	glm::mat4 getViewMatrix();
	float getZoom();
	glm::vec3 getPosition();
	void lookAlongVector(glm::vec3 vector);
private:
	void updateCameraVectors(glm::vec3);
	void updateCameraVectors();
};

