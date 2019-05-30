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
	Window* window;
	Sprite* logo;
	Layer* layer;
	Label* fps;
	Label* ups;
	BatchRenderer2D* renderer;
public:
	Game() {}

	// On Begin
	void init() override
	{
		window = createWindow("Game", 960, 540, false);

		renderer = new BatchRenderer2D();
		layer = new Layer(renderer, new Shader("shaders/basic.vert", "shaders/basic.frag"), maths::mat4::othographic(-16, 16, -9.0f, 9.0f, -1.0f, 1.0f));


		fps = new Label("5000", -15.5f, 7.5f, "mario", 42, 0xff0000ff);
		ups = new Label("60", 14.0f, 7.5f, "arial", 42, 0xff0000ff);


		logo = new Sprite(-6, 0, 10, 8, "logo.png");
		Sprite* wall = new Sprite(0, -3, 2, 6, 0xff00ffff);

		wall->setColision(true);

		logo->setColision(true);
		layer->add(new Label("Welcome to", -9.5f, 5, "mario", 80, 0xff00ffff));
		layer->add(new Label("Clownfish!", -8, 3, "mario", 80, 0xff00ffff));
		AudioManager::add(new AudioClip("background", "zelda.wav"));

		layer->add(wall);
		layer->add(logo);
		layer->add(fps);
		layer->add(ups);
		AudioManager::get("background")->loop();
	}

	// Once per Second
	void tick() override
	{
		std::cout << std::to_string(getFPS()) << " , " << std::to_string(getUPS()) << std::endl;
		fps->text = std::to_string(getFPS());
		ups->text = std::to_string(getUPS());
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
		glClearColor(0, 0, 0.8f, 1);
		layer->render();
		AudioManager::update();
	}

};