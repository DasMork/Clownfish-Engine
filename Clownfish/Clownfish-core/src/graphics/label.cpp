#include "label.h"

namespace clownfish {
	namespace graphics
	{
		Label::Label(std::string text, float x, float y, Font* font, unsigned int color)
			: Renderable2D(), text(text), position(m_Position), m_Font(font)
		{
			m_Position = maths::vec3(x, y, 0);
			m_Color = color;

		}
		Label::Label(std::string text, float x, float y, Font* font, maths::vec3 color)
			: Renderable2D(), text(text), position(m_Position), m_Font(font)
		{
			m_Position = maths::vec3(x, y, 0);
			setColor(color);
		}
		Label::Label(std::string text, float x, float y, unsigned int color)
			: Renderable2D(), text(text), position(m_Position), m_Font(FontManager::get("arial"))
		{
			m_Position = maths::vec3(x, y, 0);
			m_Color = color;

		}
		Label::Label(std::string text, float x, float y, maths::vec3 color)
			: Renderable2D(), text(text), position(m_Position), m_Font(FontManager::get("arial"))
		{
			m_Position = maths::vec3(x, y, 0);
			setColor(color);

		}
		Label::Label(std::string text, float x, float y, const std::string& font, unsigned int color)
			: Renderable2D(), text(text), position(m_Position), m_Font(FontManager::get(font))
		{
			m_Position = maths::vec3(x, y, 0);
			m_Color = color;
			validateFont(font);

		}
<<<<<<< HEAD
		Label::Label(std::string text, float x, float y, const std::string& font, maths::vec3 color)
			: Renderable2D(), text(text), position(m_Position), m_Font(FontManager::get(font))
		{
			m_Position = maths::vec3(x, y, 0);
			setColor(color);
=======
		Label::Label(std::string text, float x, float y, float textfieldsize, const std::string& font, unsigned int color)
			: Renderable2D(), text(text), position(m_Position), m_Font(FontManager::get(font)), m_TextFieldSize(textfieldsize)
		{
			m_Position = maths::vec3(x, y, 0);
			m_Color = color;
>>>>>>> 7f285629770574945df20387d990d3876248db20
			validateFont(font);

		}
		Label::Label(std::string text, float x, float y, const std::string& font, unsigned int size, unsigned int color)
			: Renderable2D(), text(text), position(m_Position), m_Font(FontManager::get(font, size))
		{
			m_Position = maths::vec3(x, y, 0);
			m_Color = color;
			validateFont(font);

		}
		Label::Label(std::string text, float x, float y, const std::string& font, unsigned int size, maths::vec3 color)
			: Renderable2D(), text(text), position(m_Position), m_Font(FontManager::get(font, size))
		{
			m_Position = maths::vec3(x, y, 0);
			setColor(color);
			validateFont(font);

		}
		void Label::submit(Renderer2D* renderer) const
		{
			renderer->drawString(text, m_TextFieldSize, *m_Font, position, m_Color);

		}
		void Label::validateFont(const std::string& name, int size)
		{
			if (m_Font != nullptr)
				return;


			if (m_Font == nullptr)
			{
				std::cout << "[GRAPHICS] FONT NOT FOUND" << std::endl;

				m_Font = FontManager::get("arial");
			}
		}

	}
}