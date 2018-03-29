#pragma once

#include "Renderable2D.h"

namespace clownfish{namespace graphics
{

class Label : public Renderable2D
{
public:

	std::string text;

public:
	Label(float x, float y, unsigned int color, std::string text);


	void submit(Renderer2D* renderer) const override;
};


} }