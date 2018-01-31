#include "Camera.h"
#include <glm\gtc\matrix_transform.hpp>

nle::Camera::Camera()
{
}

nle::Camera::~Camera()
{
}

void nle::Camera::CreateOrthographic(float left, float right, float top, float bottom, float zNear, float zFar)
{
	m_IsOrtho = true;
	m_LeftEdge = left;
	m_RightEdge = right;
	m_TopEdge = top;
	m_BottomEdge = bottom;
	m_ZNear = zNear;
	m_ZFar = zFar;
	if (zNear <= 0.0 && zFar <= 0.0)
		m_Projection = glm::ortho(left, right, bottom, top);
	else
		m_Projection = glm::ortho(left, right, bottom, top, zNear, zFar);
}

void nle::Camera::CreatePerspective(float fov, float aspectRatio, float zNear, float zFar)
{
	m_IsOrtho = false;
	m_Zoom = fov;
	m_Aspect = aspectRatio;
	m_ZNear = zNear;
	m_ZFar = zFar;
	m_Projection = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
}

void nle::Camera::SetLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	m_View = glm::lookAt(eye, center, up);
}

void nle::Camera::Move(CameraMovement movement)
{
	if (m_IsOrtho)
	{

	}
	else
	{
		if (movement == CameraMovement::UP)
		{
			m_Pitch += m_CamSpeed;
		}
		if (movement == CameraMovement::DOWN)
		{
			m_Pitch -= m_CamSpeed;
		}
		if (movement == CameraMovement::LEFT)
		{
			m_Yaw -= m_CamSpeed;
		}
		if (movement == CameraMovement::RIGHT)
		{
			m_Yaw += m_CamSpeed;
		}
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;
	}
	Update();
}

void nle::Camera::Zoom(float zoomFactor)
{
	m_Zoom += zoomFactor;
	UpdateProjection();
}

void nle::Camera::Update()
{
	if (m_IsOrtho)
	{
		m_View = glm::lookAt(m_Position, m_Front, m_Up);
	}
	else
	{
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);

		m_Right = glm::normalize(glm::cross(m_Front, glm::vec3(0, 1, 0)));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));

		m_View = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}
}
void nle::Camera::UpdateProjection()
{
	if (m_IsOrtho)
	{
		m_Projection = glm::ortho(m_LeftEdge, m_RightEdge, m_BottomEdge, m_TopEdge, m_ZNear, m_ZFar);
	}
	else
	{
		m_Projection = glm::perspective(glm::radians(m_Zoom), m_Aspect, m_ZNear, m_ZFar);
	}
}