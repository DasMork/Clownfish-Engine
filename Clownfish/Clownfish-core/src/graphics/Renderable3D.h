#pragma once
#include "..\maths\maths.h"
#include "buffers\buffer.h"
#include "buffers\indexbuffer.h"
#include "buffers\vertextarray.h"
#include "..\graphics\shader.h"
namespace clownfish {
	namespace graphics
	{
		struct VertexData3D
		{
			maths::vec3 vertex;
			// maths::vec4 color;
			unsigned int color;
		};

		class Renderable3D
		{
		protected:
			maths::vec3 m_Position;
			maths::vec2 m_Size;
			maths::vec4 m_Color;

		public:
			Renderable3D(maths::vec3 position, float edgeLength, maths::vec4 color)
				:m_Position(position), m_Size(edgeLength, edgeLength), m_Color(color)
			{

			}
			~Renderable3D()
			{

			}



			inline const maths::vec3& getPosition() const { return m_Position; }
			inline const maths::vec2& getSize() const { return m_Size; }
			inline const maths::vec4& getColor() const { return m_Color; }

		};





	}
}