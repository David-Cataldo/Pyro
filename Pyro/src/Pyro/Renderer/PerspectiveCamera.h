#pragma once

#include <stack>

#include <glm/gtx/quaternion.hpp>

#include "Pyro/Core.h"

#include "Camera.h"

namespace Pyro
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera() {}
		PerspectiveCamera(float fovy, float aspect, float zNear, float zFar);

		void SetProjection(float fovy, float aspect, float zNear, float zFar);

		glm::vec3 GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& pos) { m_Position = pos; CalculateViewMatrix(); }

		void Move(float dist, const glm::vec3& cameraAxis);
		void Rotate(float angle, const glm::vec3& axis);

		glm::vec3 CalcForwardVector();

		glm::vec3 GetForwardVector() const { return m_ForwardVector; }
		glm::quat GetRotation() const { return m_Rotation; }

		virtual const glm::mat4& GetProjectionMatrix() const override { return m_ProjectionMatrix; }
		virtual const glm::mat4& GetViewMatrix() const override { return m_ViewMatrix; }
		virtual const glm::mat4& GetViewProjectionMatrix() const override { return m_ViewProjectionMatrix; }

	private:
		virtual void CalculateViewMatrix() override;

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_ForwardVector = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::quat m_Rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		float totPitch = 0.0f;

	};
}