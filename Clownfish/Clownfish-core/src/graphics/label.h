#pragma once

#include "Renderable2D.h"
#include "fontmanager.h"

namespace clownfish{namespace graphics
{

class Label : public Renderable2D
{
public:
	Font* m_Font;
	std::string text;
	maths::vec3& position;
	float x, y;
	float m_TextFieldSize = 1000;

public:
	Label(std::string text, float x, float y, Font* font, unsigned int color);
	Label(std::string text, float x, float y, unsigned int color);
	Label(std::string text, float x, float y, const std::string& font, unsigned int color);
	Label(std::string text, float x, float y, const std::string& font, unsigned int size, unsigned int color);
	Label(std::string text, float x, float y, float textfieldsize, const std::string& font, unsigned int color);


	void submit(Renderer2D* renderer) const override;
	void validateFont(const std::string& name, int size = -1);
};


} }