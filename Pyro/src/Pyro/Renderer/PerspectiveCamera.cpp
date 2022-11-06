#include "pypch.h"
#include "PerspectiveCamera.h"

namespace Pyro
{
	PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float zNear, float zFar)
		: m_ProjectionMatrix(glm::perspective(glm::radians(fovy), aspect, zNear, zFar)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::Move(float dist, const glm::vec3& cameraAxis)
	{
		glm::vec3 normalized = glm::normalize(cameraAxis);
		glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

		// Forwards / Backwards
		m_Position += m_ForwardVector * dist * -normalized.z;
		// Up / Down
		m_Position += worldUp * dist * normalized.y;
		// Left / Right - CameraRightVector
		m_Position += glm::cross(worldUp, m_ForwardVector) * dist * normalized.x;

		CalculateViewMatrix();
	}

	void PerspectiveCamera::Rotate(float angle, const glm::vec3& axis)
	{
		if (totPitch + angle > 89.0f)
			angle = 89.0f - totPitch;

		else if (totPitch + angle < -89.0f)
			angle = -89.0f - totPitch;

		totPitch += angle;

		glm::vec3 normalized = glm::normalize(axis);
		glm::quat rot = glm::angleAxis(glm::radians(angle), axis);

		m_Rotation = glm::normalize(rot) * m_Rotation;

		m_ForwardVector = CalcForwardVector();
		CalculateViewMatrix();
	}

	glm::vec3 PerspectiveCamera::CalcForwardVector()
	{
		/* More explicit explanation:
		V[0] = 2 * (x * z - w * y)
		V[1] = 2 * (y * z + w * x)
		V[2] = 1 - 2 * (x * x + y * y)*/

		return glm::vec3(2 * (m_Rotation.x * m_Rotation.z - m_Rotation.w * m_Rotation.y),
						 2 * (m_Rotation.y * m_Rotation.z + m_Rotation.w * m_Rotation.x),
						 1 - 2 * (m_Rotation.x * m_Rotation.x + m_Rotation.y * m_Rotation.y));
	}

	void PerspectiveCamera::SetProjection(float fovy, float aspect, float zNear, float zFar)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(fovy), aspect, zNear, zFar);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::CalculateViewMatrix()
	{
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), -m_Position);
		glm::mat4 rotation = glm::mat4_cast(m_Rotation);

		m_ViewMatrix = rotation * translation;

		//glm::vec3 up = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
		//m_ViewMatrix = glm::lookAt(m_Position, m_Position + glm::vec3(0.0f, 0.0f, -1.0f), up);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}