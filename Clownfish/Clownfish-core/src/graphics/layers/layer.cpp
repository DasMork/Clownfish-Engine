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

						float sizeX = sqrt(renderable->getSize().x *renderable->getSize().x) / 2;
						float sizeY = sqrt(renderable->getSize().y* renderable->getSize().y) / 2;

						for (int z = 0; z < m_Colliders.size(); z++)
						{
							if (m_Colliders[z] != renderable)
							{
								std::cout << CheckCollision(renderable, m_Colliders[z]) << std::endl;

								if (CheckCollision(renderable, m_Colliders[z]))
									renderable->translate(maths::vec3(-renderable->getTranslation().x, -renderable->getTranslation().y, 0));

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
			// Collision x-axis?
			bool collisionX = renderable->getPosition().x + renderable->getSize().x >= other->getPosition().x&&
				other->getPosition().x + other->getSize().x >= renderable->getPosition().x;
			// Collision y-axis?
			bool collisionY = renderable->getPosition().y + renderable->getSize().y >= other->getPosition().y &&
				other->getPosition().y + other->getSize().y >= renderable->getPosition().y;
			// Collision only if on both axes
			return collisionX && collisionY;
		}

	}
}