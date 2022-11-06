#pragma once

#include "Pyro/Renderer/PerspectiveCamera.h"
#include "Pyro/Core/Timestep.h"

#include "Pyro/Events/ApplicationEvent.h"
#include "Pyro/Events/MouseEvent.h"

namespace Pyro
{
	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(float fovy, float aspect, float zNear = 0.1f, float zFar = 30.0f); 

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		PerspectiveCamera& GetCamera() { return m_Camera; }
		const PerspectiveCamera& GetCamera() const { return m_Camera; }

		glm::vec3 GetForwardVector() const { return m_Camera.GetForwardVector(); }
		glm::vec3 GetPosition() const { return m_Camera.GetPosition(); }
		glm::quat GetRotation() const { return m_Camera.GetRotation(); }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);

	private:
		float m_AspectRatio;
		float m_Fovy;
		float m_Near;
		float m_Far;
		float m_ZoomLevel = 1.0f;

		PerspectiveCamera m_Camera;

		float m_CameraRotationSpeed = 0.4f;
		float m_CameraMoveSpeed = 4.0f;

	};
}