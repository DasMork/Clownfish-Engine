#pragma once
#include <clownfish.h>

using namespace clownfish;
using namespace graphics;
using namespace input;
using namespace maths;
using namespace audio;


class Game : public Clownfish
{

private:
	Window * window;
	Sprite* logo;
	Layer* layer;
	BatchRenderer2D* renderer;
public:
	Game() {}

	// On Begin
	void init() override
	{


		window = createWindow("Game", 960, 540, false);
		renderer = new BatchRenderer2D();
		layer = new Layer(renderer, new Shader("shaders/basic.vert", "shaders/basic.frag"), maths::mat4::othographic(-16, 16, -9.0f, 9.0f, -1.0f, 1.0f));


		logo = new Sprite(-6, 0, 10, 8, "logo.png");


		layer->add(logo);

	}

	// Once per Second
	void tick() override
	{

	}


	//60 Times per Second
	void update() override
	{



	}

	//As fast as possible
	void render() override
	{
		glClearColor(0, 0, 0.8f, 1);
		layer->render();
	}

};