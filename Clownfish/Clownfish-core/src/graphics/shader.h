#pragma once
#include "../utils/fileutils.h"
#include <GL\glew.h>
#include "..\maths\maths.h"

namespace clownfish
{
	namespace graphics
	{

		class Shader
		{
		private:
			const char *m_VertPath, *m_FragPath;
			GLuint m_ShaderID;

		public:
			Shader(const char* vertexPath, const char* fragPath);
			~Shader();


			void setUniform1f(const GLchar* name, float value);
			void setUniform1i(const GLchar* name, int value);
			void setUniform2f(const GLchar* name, const maths::vec2& vector);
			void setUniform3f(const GLchar* name, const maths::vec3& vector);
			void setUniform4f(const GLchar* name, const maths::vec4& vector);

			void setUniformMat4(const GLchar* name, const maths::mat4& matrix);

			
			void enable() const;
			void disable() const;

		private: 
			GLuint load();
			GLint getUniformLocation(const GLchar* name);


		};


	}
}