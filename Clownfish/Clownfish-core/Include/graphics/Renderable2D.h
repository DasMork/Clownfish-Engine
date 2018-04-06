#pragma once
#include "..\maths\maths.h"
#include "buffers\buffer.h"
#include "buffers\indexbuffer.h"
#include "buffers\vertextarray.h"
#include "..\graphics\shader.h"
#include "renderer2d.h"
#include "Renderable2D.h"
#include "texture.h"

namespace clownfish {
	namespace graphics
	{
		struct VertexData
		{
			maths::vec3 vertex;
			maths::vec2 uv;
			float tid;
			unsigned int color;
		};

		class Renderable2D
		{
		protected:
			maths::vec3 m_Position;
			maths::vec2 m_Size;
			unsigned int m_Color;
			std::vector<maths::vec2> m_UV;
			Texture* m_Texture;

			maths::vec3 m_Translation;
			bool m_HasCollision = false;
			bool m_HasMoved = false;
		protected:
			Renderable2D()
			{
				setUVDefaults();
			}
		public:
			Renderable2D(maths::vec3 position, maths::vec2 size, unsigned int color)
				:m_Position(position), m_Size(size), m_Color(color)
			{
				setUVDefaults();

			}
			~Renderable2D()
			{

			}
			virtual void submit(Renderer2D* renderer) const
			{
				renderer->submit(this);
			}


			virtual void translate(maths::vec3 translation)
			{
				m_Position += translation;

				m_Translation = translation;
				m_HasMoved = true;

		

			}
			virtual void scale(maths::vec2 scale)
			{
				m_Size = scale;
			}
			void setColor(unsigned int color) { m_Color = color; }
			void setColor(maths::vec4 color)
			{
				int r = color.x * 255.0f;
				int g = color.y * 255.0f;
				int b = color.z * 255.0f;
				int a = color.w * 255.0f;

				m_Color = a << 24 | b << 16 | g << 8 | r;
			}
			void setColision(bool activateCollision) { m_HasCollision = activateCollision; }


			inline const maths::vec3& getPosition() const { return m_Position; }
			inline const maths::vec3& getTranslation() const { return m_Translation; }

			inline const maths::vec2& getSize() const { return m_Size; }
			inline const unsigned int getColor() const { return m_Color; }
			inline const std::vector<maths::vec2>& getUV() const { return m_UV; }
			inline const bool hasCollision() const { return m_HasCollision; }
			inline const bool hasMoved() const { return m_HasMoved; }

			inline const GLuint getTID() const { return m_Texture == nullptr ? 0 : m_Texture->getID(); }

		private:
			void setUVDefaults()
			{
				m_UV.push_back(maths::vec2(0, 0));
				m_UV.push_back(maths::vec2(0, 1));
				m_UV.push_back(maths::vec2(1, 1));
				m_UV.push_back(maths::vec2(1, 0));
			}

		};





	}
}