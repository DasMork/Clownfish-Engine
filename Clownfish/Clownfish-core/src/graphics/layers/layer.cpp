#include "layer.h"


namespace clownfish {
	namespace graphics {


		Layer::Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projectionMatrix)
			: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix)
		{
			m_Shader->enable();
			m_Shader->setUniformMat4("pr_matrix", m_ProjectionMatrix);

			GLint texIDs[32] =
			{
				0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,23,24,25,26,27,28,29,30,31
			};

			m_Shader->setUniform1iv("textures", texIDs, 10);

			m_Shader->disable();

		}

		Layer::~Layer()
		{
			delete m_Shader;
			delete m_Renderer;
			for (int i = 0; i < m_Renderables.size(); i++)
			{
				delete m_Renderables[i];
			}

		}


		void Layer::add(Renderable2D* renderable)
		{
			m_Renderables.push_back(renderable);

			if (renderable->hasCollision())
				m_Colliders.push_back(renderable);
		}

		void Layer::render()
		{

			m_Shader->enable();

			m_Renderer->begin();
			int i = 0;

			if (m_Colliders.size() > 0)
			{
				for (int i = 0; i < m_Colliders.size(); i++)
				{
					if (m_Colliders[i]->hasMoved())
					{
						Renderable2D* renderable = m_Colliders[i];

						

						for (int z = 0; z < m_Colliders.size(); z++)
						{
							if (m_Colliders[z] != renderable)
							{
								CheckCollision(renderable, m_Colliders[z]);
									//OnCollisionEnter();
							}
						}
					}
				}
			}


			for (const Renderable2D* renderable : m_Renderables)
			{

				renderable->submit(m_Renderer);
			}
			m_Renderer->end();
			m_Renderer->flush();


		}

		bool Layer::CheckCollision(Renderable2D* renderable, Renderable2D* other) // AABB - AABB collision
		{
			float sizeX = sqrt(renderable->getSize().x *renderable->getSize().x) / 2;
			float sizeY = sqrt(renderable->getSize().y* renderable->getSize().y) / 2;

			float otherSizeX = sqrt(other->getSize().x *other->getSize().x) / 2;
			float otherSizeY = sqrt(other->getSize().y* other->getSize().y) / 2;

			// Collision x-axis?
			bool collisionX = renderable->getPosition().x + sizeX > other->getPosition().x - otherSizeX &&
				other->getPosition().x + otherSizeX > renderable->getPosition().x - sizeX;
			// Collision y-axis?
			bool collisionY = renderable->getPosition().y + sizeY > other->getPosition().y - otherSizeY &&
				other->getPosition().y + otherSizeY > renderable->getPosition().y - sizeY;
			// Collision only if on both axes

			if(collisionX && collisionY)
			{
			renderable->translate(maths::vec3(-renderable->getTranslation().x, -renderable->getTranslation().y, -renderable->getTranslation().z));
			}
			
			return collisionX && collisionY;
		}

	}
}