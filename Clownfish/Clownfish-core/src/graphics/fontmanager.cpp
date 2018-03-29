#include "fontmanager.h"

namespace clownfish {
	namespace graphics
	{
		std::vector<Font*> FontManager::m_Fonts;

		void FontManager::add(Font* font)
		{
			m_Fonts.push_back(font);
		}
		Font* FontManager::get(const std::string& name)
		{
			for(Font* font : m_Fonts)
			{
				if (font->getName() == name)
					return font;
			}
			return nullptr; 
		}
		Font* FontManager::get(const std::string& name, unsigned int size)
		{
			for (Font* font : m_Fonts)
			{
				if (font->getSize() == size && font->getName() == name)
					return font;
			}
			for (Font* font : m_Fonts)
			{
				if (font->getName() == name)
					return new Font(name, font->getFilename(), size);
			}
			return nullptr;
		}
		void FontManager::clean()
		{
			for (int i; i < m_Fonts.size(); i++)
			{
				delete m_Fonts[i];
			}
		}





	}
}