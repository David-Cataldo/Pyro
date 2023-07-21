#include "pypch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Pyro
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		PY_CORE_ASSERT(windowHandle, "Window handle is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PY_CORE_ASSERT(status, "Failed to initialize Glad!");

		PY_CORE_INFO("OpenGL Info:");
		PY_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		PY_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		PY_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}