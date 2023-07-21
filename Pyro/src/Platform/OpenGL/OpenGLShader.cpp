#include "pypch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Pyro
{
	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_RendererID(0)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		std::string code = ReadFile(vertexSrc);
		const GLchar* source = code.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			PY_CORE_ERROR("{0}", infoLog.data());
			PY_CORE_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated
		code = ReadFile(fragmentSrc);
		source = code.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			PY_CORE_ERROR("{0}", infoLog.data());
			PY_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		// Link our program
		glLinkProgram(m_RendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_RendererID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			PY_CORE_ERROR("{0}", infoLog.data());
			PY_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteShader(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
		m_Bound = true;
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
		m_Bound = false;
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float val)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if(location == -1)
			PY_WARN("Uniform location not found");
		glUniform1f(location, val);
		if (unbind)
			Unbind();
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& vec)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			PY_WARN("Uniform location not found");
		glUniform2fv(location, 1, glm::value_ptr(vec));
		if (unbind)
			Unbind();
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& vec)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			PY_WARN("Uniform location not found");
		glUniform3fv(location, 1, glm::value_ptr(vec));
		if (unbind)
			Unbind();
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& vec)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			PY_WARN("Uniform location not found");
		glUniform4fv(location, 1, glm::value_ptr(vec));
		if (unbind)
			Unbind();
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			PY_WARN("Uniform location not found");
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
		if (unbind)
			Unbind();
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			PY_WARN("Uniform location not found");
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
		if(unbind)
			Unbind();
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int val)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			PY_WARN("Uniform location not found");
		glUniform1i(location, val);
		if (unbind)
			Unbind();
	}

	void OpenGLShader::UploadUniformInt2(const std::string& name, const glm::ivec2& vec)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			PY_WARN("Uniform location not found");
		glUniform2iv(location, 1, glm::value_ptr(vec));
		if (unbind)
			Unbind();
	}

	void OpenGLShader::UploadUniformInt3(const std::string& name, const glm::ivec3& vec)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			PY_WARN("Uniform location not found");
		glUniform3iv(location, 1, glm::value_ptr(vec));
		if (unbind)
			Unbind();
	}

	void OpenGLShader::UploadUniformInt4(const std::string& name, const glm::ivec4& vec)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			PY_WARN("Uniform location not found");
		glUniform4iv(location, 1, glm::value_ptr(vec));
		if (unbind)
			Unbind();
	}

	void OpenGLShader::UploadUniformBool(const std::string& name, bool val)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			PY_WARN("Uniform location not found");
		glUniform1i(location, val); 
		if (unbind)
			Unbind();
	}






	void OpenGLShader::UploadUniformFloatArray(const std::string& name, float* val, int count)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		PY_ASSERT(location != -1, "Uniform location not found");
		glUniform1fv(location, count, val);
		if (unbind)
			Unbind();
	}

	void OpenGLShader::UploadUniformFloat2Array(const std::string& name, float* vec, int count)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		PY_ASSERT(location != -1, "Uniform location not found");
		glUniform2fv(location, count, vec);
		if (unbind)
			Unbind();
	}

	void OpenGLShader::UploadUniformFloat3Array(const std::string& name, float* vec, int count)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		PY_ASSERT(location != -1, "Uniform location not found");
		glUniform3fv(location, count, vec);
		if (unbind)
			Unbind();
	}

	void OpenGLShader::UploadUniformFloat4Array(const std::string& name, float* vec, int count)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		PY_ASSERT(location != -1, "Uniform location not found");
		glUniform4fv(location, count, vec);
		if (unbind)
			Unbind();
	}

	void OpenGLShader::UploadUniformMat3Array(const std::string& name, float* matrix, int count)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		PY_ASSERT(location != -1, "Uniform location not found");
		glUniformMatrix3fv(location, count, GL_FALSE, matrix);
		if (unbind)
			Unbind();
	}

	void OpenGLShader::UploadUniformMat4Array(const std::string& name, float* matrix, int count)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		PY_ASSERT(location != -1, "Uniform location not found");
		glUniformMatrix4fv(location, count, GL_FALSE, matrix);
		if (unbind)
			Unbind();
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* val, int count)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		PY_ASSERT(location != -1, "Uniform location not found");
		glUniform1iv(location, count, val);
		if (unbind)
			Unbind();
	}

	void OpenGLShader::UploadUniformInt2Array(const std::string& name, int* vec, int count)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		PY_ASSERT(location != -1, "Uniform location not found");
		glUniform2iv(location, count, vec);
		if (unbind)
			Unbind();
	}

	void OpenGLShader::UploadUniformInt3Array(const std::string& name, int* vec, int count)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		PY_ASSERT(location != -1, "Uniform location not found");
		glUniform3iv(location, count, vec);
		if (unbind)
			Unbind();
	}

	void OpenGLShader::UploadUniformInt4Array(const std::string& name, int* vec, int count)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		PY_ASSERT(location != -1, "Uniform location not found");
		glUniform4iv(location, count, vec);
		if (unbind)
			Unbind();
	}

	void OpenGLShader::UploadUniformBoolArray(const std::string& name, bool* val, int count)
	{
		bool unbind = !m_Bound;
		Bind();
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		PY_ASSERT(location != -1, "Uniform location not found");
		glUniform1iv(location, count, (int*)val);
		if (unbind)
			Unbind();
	}
}
