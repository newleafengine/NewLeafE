#pragma once
#include <glm\mat4x4.hpp>

namespace nle 
{
	// This defines the direction a camera is moving in a certain frame
	enum class CameraMovement { UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARD};
	
	class Camera
	{
	public:
		Camera();
		~Camera();
		
		// Controls the type of camera to be created
		void CreateOrthographic(float left, float right, float top, float bottom, float zNear = 0.0, float zFar = 0.0);
		void CreatePerspective(float fov, float aspectRatio, float zNear, float zFar);

		void SetLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up);

		void Move(CameraMovement movement);
		void Zoom(float zoomFactor);
		void Update();
		void UpdateProjection();

		// The following functions will retrieve the view, projection matrices in different configurations
		glm::mat4& GetView() { return m_View; }
		glm::mat4& GetProjection() { return m_Projection; }

		float GetZoom() { return m_Zoom; }
		bool GetCameraType() { return m_IsOrtho; }
	private:
		glm::mat4 m_View, m_Projection;
		// These are the camera vectors that control position, up dir, and right dir
		glm::vec3 m_Position, m_Forward, m_Up, m_Right, m_Front;
		float m_Yaw = -90.0f, m_Pitch = 0.0f, m_CamSpeed = 2.5f;
		bool m_IsOrtho;
		// Ortho Params
		float m_LeftEdge, m_RightEdge, m_BottomEdge, m_TopEdge;
		// Persp Params
		float m_Zoom = 45.0f;
		float m_Aspect;

		float m_ZNear, m_ZFar;
	};
}