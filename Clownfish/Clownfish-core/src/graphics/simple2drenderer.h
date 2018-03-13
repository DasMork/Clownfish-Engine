#pragma once

#include <deque>
#include "renderer2d.h"
#include "static_sprite.h"

namespace clownfish {
	namespace graphics
	{

		class Simple2DRenderer : Renderer2D
		{

		private:
			std::deque<const StaticSprite*> m_RenderQueue;

		public:
			virtual void submit(const Renderable2D* renderable) override;
			virtual void flush()override;

		};



	}
}
