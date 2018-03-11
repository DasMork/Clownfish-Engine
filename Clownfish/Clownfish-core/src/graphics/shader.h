#pragma once
#include "../utils/fileutils.h"
#include <GL\glew.h>


namespace clownfish
{
	namespace graphics
	{

		class Shader
		{
		private:
			const char *m_VertPath, *m_FragPath;

		public:
			GLuint m_ShaderID;
			Shader(const char* vertexPath, const char* fragPath);
			~Shader();

			void enable() const;
			void disable() const;

		private: 
			GLuint load();


		};


	}
}