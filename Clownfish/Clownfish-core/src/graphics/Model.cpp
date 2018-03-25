#include "Model.h"

namespace clownfish {
	namespace graphics
	{

		Model::Model(maths::vec3 position, float edgeLength, const maths::vec4& color, Shader& shader)
			: Renderable3D(position, edgeLength, color), m_Shader(shader)
		{
			m_VertexArray = new VertexArray();
			int offset = 0;



			GLfloat colors[] =
			{
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,


				color.x - 1, color.y + 1, color.z, color.w,
				color.x - 1, color.y + 1, color.z, color.w,
				color.x - 1, color.y + 1, color.z, color.w,
				color.x - 1, color.y + 1, color.z, color.w,

			};

			float r = edgeLength / 2;
			GLfloat cube_Vertices[] = {


				// front
				position.x - r, position.y - r,  position.z + r,
				position.x + r, position.y - r,  position.z + r,
				position.x + r, position.y + r,  position.z + r,
				position.x - r, position.y + r,  position.z + r,
				// back
				position.x - r, position.y - r,  position.z - r,
				position.x + r, position.y - r,  position.z - r,
				position.x + r, position.y + r,  position.z - r,
				position.x - r, position.y + r,  position.z - r,


			};
			GLushort cube_Indices[] = {
				// front
				0, 1, 2,
				2, 3, 0,
				// top
				1, 5, 6,
				6, 2, 1,
				// back
				7, 6, 5,
				5, 4, 7,
				// bottom
				4, 0, 3,
				3, 7, 4,
				// left
				4, 5, 1,
				1, 0, 4,
				// right
				3, 2, 6,
				6, 7, 3,
			};
			m_VertexArray->addBuffer(new Buffer(cube_Vertices, 8 * 3, 3), 0);
			m_VertexArray->addBuffer(new Buffer(colors, 8 * 4, 4), 1);

			m_IndexBuffer = new IndexBuffer(cube_Indices, 36);

		}
		Model::~Model()
		{
			delete m_VertexArray;
			delete m_IndexBuffer;
		}
	}
}