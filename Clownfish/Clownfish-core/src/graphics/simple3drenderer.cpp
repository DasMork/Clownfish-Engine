#include "simple3drenderer.h"

namespace clownfish {
	namespace graphics
	{

		void Simple3DRenderer::submit(const Renderable3D* renderable)
		{
			m_RenderQueue.push_back((Model*)renderable);
		}

		void Simple3DRenderer::flush()
		{
		while(!m_RenderQueue.empty())
		{
		
			const Model* model = (Model*)m_RenderQueue.front();
			model->getVAO()->bind();
			model->getIBO()->bind();

//			model->getShader().setUniformMat4("ml_matrix", maths::mat4::translation(model->getPosition()));


			glEnable(GL_DEPTH_TEST); // Tiefentest (mit dem Z-Buffer) aktivieren
			glDepthFunc(GL_LESS);
			glClear(GL_DEPTH_BUFFER_BIT);

			glDrawElements(GL_TRIANGLES, model->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

			model->getVAO()->unbind();
			model->getIBO()->unbind();

			m_RenderQueue.pop_front();
		}
		}

	}
}