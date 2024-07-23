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
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw;
	float pitch;

	float movementSpeed;
	float mouseSensitivity;
	float zoom;
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
	glm::vec3 getDirection();
	void lookAlongVector(glm::vec3 vector);
private:
	void updateCameraVectors(glm::vec3);
	void updateCameraVectors();
};

