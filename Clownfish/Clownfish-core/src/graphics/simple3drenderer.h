#pragma once

#include <deque>
#include "renderer3d.h"
#include "Model.h"

namespace clownfish {
	namespace graphics
	{

		class Simple3DRenderer : Renderer3D
		{

		private:
			std::deque<const Renderable3D*> m_RenderQueue;

		public:
			virtual void submit(const Renderable3D* renderable) override;
			virtual void flush()override;

		};



	}
}
