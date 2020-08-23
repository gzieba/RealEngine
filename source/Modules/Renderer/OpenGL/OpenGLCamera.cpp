#include "OpenGLCamera.h"

#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

#include "Modules/Renderer/Window.h"
#include "Common/logging.h"

namespace
{
constexpr auto DEFAULT_CAMERA_SPEED = 2.5f;
constexpr auto DEFAULT_FOV = 45.0f;
constexpr auto DEFAULT_TARGET_POSITION_VECTOR = glm::vec3(0.0f, 0.0f, 0.0f);
constexpr auto MAX_PITCH = 89.0f;
constexpr auto MIN_PITCH = -89.0f;
constexpr auto STARTING_CAMERA_FRONT_VECTOR = glm::vec3(0.0f, 0.0f, -1.0f);
constexpr auto STARTING_CAMERA_POSITION_VECTOR = glm::vec3(0.0f, 0.0f, 0.0f);
constexpr auto UP_VECTOR = glm::vec3(0.0f, 1.0f, 0.0f);
}

OpenGLCamera::OpenGLCamera(Window* window)
	: m_window(window), m_viewMatrix(glm::mat4(1.0f))
{
	m_cameraPosition = STARTING_CAMERA_POSITION_VECTOR;
	m_cameraSpeed = DEFAULT_CAMERA_SPEED;

	m_cameraFront = STARTING_CAMERA_FRONT_VECTOR;

	glfwSetInputMode(m_window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	lookAt(DEFAULT_TARGET_POSITION_VECTOR);
}

glm::mat4 OpenGLCamera::getViewMatrix() const
{
	return m_viewMatrix;
}

void OpenGLCamera::lookAt(glm::vec3 position)
{
	m_viewMatrix = glm::lookAt(m_cameraPosition, position, UP_VECTOR);
}

void OpenGLCamera::update()
{
	double xPos, yPos;
	glfwGetCursorPos(m_window->getWindow(), &xPos, &yPos);

	mouseInput(xPos, yPos);

	if (glfwGetKey(m_window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		m_cameraPosition += m_cameraSpeed * m_cameraFront * 16.6f;
	}
	if (glfwGetKey(m_window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		m_cameraPosition -= m_cameraSpeed * m_cameraFront * 16.6f;
	}
	if (glfwGetKey(m_window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		m_cameraPosition -= glm::normalize(glm::cross(m_cameraFront, UP_VECTOR)) * m_cameraSpeed * 16.6f;
	}
	if (glfwGetKey(m_window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		m_cameraPosition += glm::normalize(glm::cross(m_cameraFront, UP_VECTOR)) * m_cameraSpeed * 16.6f;
	}
	if(glfwGetKey(m_window->getWindow(), GLFW_KEY_E) == GLFW_PRESS)
	{
		m_cameraPosition += m_cameraSpeed * UP_VECTOR * 16.6f;
	}
	if(glfwGetKey(m_window->getWindow(), GLFW_KEY_Q) == GLFW_PRESS)
	{
		m_cameraPosition -= m_cameraSpeed * UP_VECTOR * 16.6f;
	}

//	LOG(TRACE) << LOCATION << m_cameraPosition.x << " " << m_cameraPosition.y << " " << m_cameraPosition.z;

	lookAt(m_cameraPosition + m_cameraFront);
}

float OpenGLCamera::getFOV() const
{
	return DEFAULT_FOV;
}

glm::vec3 OpenGLCamera::getPosition() const
{
	return m_cameraPosition;
}

void OpenGLCamera::mouseInput(float xPosition, float yPosition)
{
	if(m_isFirstMove)
	{
		m_lastXPosition = xPosition;
		m_lastYPosition = yPosition;
		m_isFirstMove = false;
	}

	float xOffset = xPosition - m_lastXPosition;
	float yOffset = m_lastYPosition - yPosition;
	m_lastXPosition = xPosition;
	m_lastYPosition = yPosition;

	xOffset *= m_mouseSensitivity;
	yOffset *= m_mouseSensitivity;

	m_yaw += xOffset;
	m_pitch += yOffset;

	if(m_pitch > MAX_PITCH)
		m_pitch = MAX_PITCH;
	if(m_pitch < MIN_PITCH)
		m_pitch = MIN_PITCH;

	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_cameraFront = glm::normalize(front);
}
