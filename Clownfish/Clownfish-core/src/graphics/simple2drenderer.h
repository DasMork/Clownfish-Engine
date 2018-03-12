#pragma once

#include <deque>
#include "renderer2d.h"

namespace clownfish {
	namespace graphics
	{

		class Simple2DRenderer : Renderer2D
		{

		private:
			std::deque<const Renderable2D*> m_RenderQueue;

		public:
			virtual void submit(const Renderable2D* renderable) override;
			virtual void flush()override;

		};



	}
}
