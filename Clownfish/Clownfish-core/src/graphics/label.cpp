#include "label.h"

namespace clownfish {
	namespace graphics
	{
		Label::Label(float x, float y, unsigned int color, std::string text)
			: Renderable2D(), text(text)
		{
			m_Position = maths::vec3(x, y, 0);
			m_Color = color;
		}

		void Label::submit(Renderer2D* renderer) const
		{
			renderer->drawString(text, m_Position, m_Color);
		
		}
	}
}