#pragma once

#include "Renderable3D.h"

namespace clownfish {
	namespace graphics
	{
		class Model : public Renderable3D
		{
		private:

			VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;
			Shader& m_Shader;
		public:
			Model(maths::vec3 position, float edgeLength, const maths::vec4& color, Shader& shader);
			~Model();

			inline const VertexArray* getVAO() const { return m_VertexArray; }
			inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }
			inline  Shader& getShader() const { return m_Shader; }
		};


	}
}