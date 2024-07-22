#include "pypch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>

#include "../vendor/stbi/include/stb_image.h"

namespace Pyro
{
	 uint32_t OpenGLTexture::s_PlainTextureID;


	OpenGLTexture::OpenGLTexture(const std::string& fileLoc)
		: m_FileLoc(fileLoc), m_TextureID(0)
	{}

	OpenGLTexture::OpenGLTexture()
		: m_FileLoc("Assets/Textures/plain.png"), m_TextureID(0)
	{}

	OpenGLTexture::~OpenGLTexture()
	{
		ClearTexture();
	}

	bool OpenGLTexture::LoadTexture()
	{
		int width, height, bitDepth;
		unsigned char* textData = stbi_load(m_FileLoc.c_str(), &width, &height, &bitDepth, 0);
		if (!textData)
		{
			PY_ERROR("Error loading texture at: %s", m_FileLoc);
			m_TextureID = s_PlainTextureID;
			return false;
		}

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(textData);

		return true;
	}

	bool OpenGLTexture::LoadTextureAlpha()
	{
		int width, height, bitDepth;
		unsigned char* textData = stbi_load(m_FileLoc.c_str(), &width, &height, &bitDepth, 0);
		if (!textData)
		{
			PY_ERROR("Error loading texture at: %s", m_FileLoc);
			m_TextureID = s_PlainTextureID;
			return false;
		}

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(textData);

		return true;
	}

	
	bool OpenGLTexture::LoadPlainTexture()
	{
		int width, height, bitDepth;
		unsigned char* textData = stbi_load("Assets/Textures/plain.png", &width, &height, &bitDepth, 0);
		if (!textData)
		{
			PY_ERROR("Error loading texture at:");
			return false;
		}

		glGenTextures(1, &s_PlainTextureID);
		glBindTexture(GL_TEXTURE_2D, s_PlainTextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(textData);

		return true;
	}
	

	void OpenGLTexture::Bind()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void OpenGLTexture::Unbind()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLTexture::ClearTexture()
	{
		glDeleteTextures(1, &m_TextureID);
		m_TextureID = 0;
		m_FileLoc = "";
	}
}