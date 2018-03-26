#pragma once

#include "..\renderer2d.h"
#include "..\Renderable2D.h"


namespace clownfish {
	namespace graphics {

		class Layer
		{
		protected:
			Renderer2D* m_Renderer;
			std::vector<Renderable2D*> m_Renderables;
			Shader* m_Shader;
			maths::mat4 m_ProjectionMatrix;
			
		public:
			Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projectionMatrix);
			virtual ~Layer();
			virtual void add(Renderable2D* renderable);
			virtual void render();
		protected:

		};






} }