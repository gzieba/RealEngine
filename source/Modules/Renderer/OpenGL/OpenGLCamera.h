#pragma once

#include <glm/glm.hpp>

class Window;

class OpenGLCamera
{
	Window* m_window;

	glm::vec3 m_cameraPosition;
	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraUp;

	float m_cameraSpeed;

	glm::mat4 m_viewMatrix;

public:
	OpenGLCamera(Window* window);

	glm::mat4 GetViewMatrix() const;
	void LookAt(glm::vec3 position);
	void Update();
	float GetFOV() const;
	glm::vec3 GetPosition() const;

private:
	void MouseInput(float xPosition, float yPosition);

	float m_mouseSensitivity = 0.05f;

	bool m_isFirstMove = true;

	float m_lastXPosition;
	float m_lastYPosition;

	float m_yaw = 0.0f;
	float m_pitch = 0.0f;
};
