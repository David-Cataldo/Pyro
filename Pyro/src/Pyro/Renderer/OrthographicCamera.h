#pragma once

#include "Camera.h"

namespace Pyro
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera() {}
		OrthographicCamera(float left, float right, float bottom, float top);

		virtual const glm::vec3& GetPosition() const override { return m_Position; } 
		virtual void SetPosition(const glm::vec3& pos) override { m_Position = pos; CalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; CalculateViewMatrix(); }

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
		float m_Rotation = 0.0f;
	};
}