#pragma once

// For use by Pyro applications

#include "Pyro/Application.h"
#include "Pyro/Layer.h"
#include "Pyro/Log.h"

#include "Pyro/Core/Timestep.h"

#include "Pyro/MouseButtonCodes.h"
#include "Pyro/KeyCodes.h"
#include "Pyro/Input.h"
#include "Pyro/PerspectiveCameraController.h"

#include "Pyro/ImGui/ImGuiLayer.h"
#include "Pyro/ImGui/ImGUIComponent.h"
#include "Pyro/ImGui/ImGUISlider.h"

// ---Renderer-----------------------
#include "Pyro/Renderer/Renderer.h"
#include "Pyro/Renderer/RenderCommand.h"

#include "Pyro/Renderer/Buffer.h"
#include "Pyro/Renderer/Shader.h"
#include "Pyro/Renderer/VertexArray.h"
#include "Pyro/Renderer/Material.h"
#include "Pyro/Renderer/Texture.h"
#include "Pyro/Renderer/Model.h"

#include "Pyro/Renderer/Camera.h"
#include "Pyro/Renderer/OrthographicCamera.h"
#include "Pyro/Renderer/PerspectiveCamera.h"

#include "Pyro/Renderer/Light.h"
#include "Pyro/Renderer/PointLight.h"
// ----------------------------------

// ---Entry Point--------------------
#include "Pyro/EntryPoint.h"
// ----------------------------------

#include "Pyro/ECS_Components/TransformComponent.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../vendor/stbi/include/stb_image.h"

