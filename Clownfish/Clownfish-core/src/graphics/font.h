#pragma once
#include "..\..\ext\freetype-gl\freetype-gl.h"
#include <string>
namespace clownfish{namespace graphics
{

	class Font
	{
private:
	ftgl::texture_atlas_t* m_FTAtlas;
	ftgl::texture_font_t* m_FTFont;

	std::string m_Filename;
	std::string m_Name;

	unsigned int m_Size;

	public:
		Font(std::string name, std::string filename, int size);


		inline 	ftgl::texture_font_t* getFTFont() const { return m_FTFont; }

		inline const int getID() const { return m_FTAtlas->id; }
		inline const std::string& getName() const { return m_Name; }
		inline const std::string& getFilename() const { return m_Filename; }
		inline const unsigned int getSize() const { return m_Size; }

	};

}}