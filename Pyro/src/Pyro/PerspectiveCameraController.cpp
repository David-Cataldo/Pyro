#include "pypch.h"
#include "PerspectiveCameraController.h"

#include "Pyro/Core.h"

#include "Pyro/Input.h"
#include "Pyro/KeyCodes.h"
#include "Pyro/MouseButtonCodes.h"

namespace Pyro
{
	PerspectiveCameraController::PerspectiveCameraController(float fovy, float aspect, float zNear, float zFar)
		: m_Camera(fovy, aspect, zNear, zFar), m_Fovy(fovy), m_AspectRatio(aspect), m_Near(zNear), m_Far(zFar)
	{

	}

	void PerspectiveCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(PY_KEY_A))
			m_Camera.Move(-m_CameraMoveSpeed * ts, PY_X_AXIS);
		else if (Input::IsKeyPressed(PY_KEY_D))
			m_Camera.Move(m_CameraMoveSpeed * ts, PY_X_AXIS);

		if (Input::IsKeyPressed(PY_KEY_S))
			m_Camera.Move(-m_CameraMoveSpeed * ts, PY_Z_AXIS);
		else if (Input::IsKeyPressed(PY_KEY_W))
			m_Camera.Move(m_CameraMoveSpeed * ts, PY_Z_AXIS);

		if (Input::IsKeyPressed(PY_KEY_SPACE))
			m_Camera.Move(m_CameraMoveSpeed * ts, PY_Y_AXIS);
		else if (Input::IsKeyPressed(PY_KEY_LEFT_SHIFT))
			m_Camera.Move(-m_CameraMoveSpeed * ts, PY_Y_AXIS);
	}

	void PerspectiveCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(PY_BIND_EVENT_FN(PerspectiveCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(PY_BIND_EVENT_FN(PerspectiveCameraController::OnWindowResized));
		dispatcher.Dispatch<MouseMovedEvent>(PY_BIND_EVENT_FN(PerspectiveCameraController::OnMouseMoved));
	}

	bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset();
		m_Camera.SetProjection(m_Fovy * m_ZoomLevel, m_AspectRatio, m_Near, m_Far);
		return false;
	}

	bool PerspectiveCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(m_Fovy * m_ZoomLevel, m_AspectRatio, m_Near, m_Far);
		return false;
	}

	bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent& e)
	{
		if (Input::IsMouseButtonPressed(PY_MOUSE_BUTTON_LEFT))
		{
			if (abs(e.GetX() * m_CameraRotationSpeed) > 0.1)
				m_Camera.Rotate(e.GetX() * m_CameraRotationSpeed, PY_Y_AXIS);
			if (abs(e.GetY() * m_CameraRotationSpeed) > 0.1)
				m_Camera.Rotate(e.GetY() * m_CameraRotationSpeed, PY_X_AXIS);
			//std::cout << "Mx: " << e.GetX() << ", My: " << e.GetY() << std::endl;
		}


		return false;
	}
}