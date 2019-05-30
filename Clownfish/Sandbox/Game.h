#pragma once
#include <clownfish.h>

using namespace clownfish;
using namespace graphics;
using namespace input;
using namespace maths;
//using namespace audio;

class Game : public Clownfish
{

private:
	Window * window;
	BatchRenderer2D* renderer;
	Layer* layer;
	Sprite* logo;


public:
	Game() {}

	// On Begin
	void init() override
	{
		window = createWindow("Sandbox", 960, 540, false);

		renderer = new BatchRenderer2D();
		layer = new Layer(renderer, new Shader("shaders/basic.vert", "shaders/basic.frag"), maths::mat4::othographic(-16, 16, -9.0f, 9.0f, -1.0f, 1.0f));

		logo = new Sprite(0, 0, 10, 8, "logo.png");
		layer->add(logo);
		Font* font = new Font("arial", "fonts/arial", 45);
		layer->add(new Label("Janik stinkt!", 0, 5, FontManager::get("arial"), Color::YellowGreen));


	}

	// Once per Second
	void tick() override
	{



	}


	//60 Times per Second
	void update() override
	{

		float x = Input::GetAxis(HORIZONTAL);
		float y = Input::GetAxis(VERTICAL);

		if (x > 0.1f)
			logo->scale(vec2(-10, 8));

		if (x < -0.1f)
			logo->scale(vec2(10, 8));

		logo->translate(vec3(x * 0.5f, y * 0.5f, 0));

	}

	//As fast as possible
	void render() override
	{
		layer->render();
	}

};
