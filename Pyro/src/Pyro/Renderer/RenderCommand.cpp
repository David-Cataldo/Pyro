#include "pypch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Pyro
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}