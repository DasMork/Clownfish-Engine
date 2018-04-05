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
			std::vector<Renderable2D*> m_Colliders;
			Shader* m_Shader;
			maths::mat4 m_ProjectionMatrix;
			
			bool CheckCollision(Renderable2D* renderable, Renderable2D* other);

		public:
			Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projectionMatrix);
			virtual ~Layer();
			virtual void add(Renderable2D* renderable);
			virtual void render();


			inline const Renderer2D* getRenderer() const { return m_Renderer; }
		protected:

		};






} }