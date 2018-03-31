#include "..\src\clownfish.h"


using namespace clownfish;
using namespace graphics;
using namespace input;
using namespace maths;
using namespace audio;

class Game : public Clownfish
{

private:
	Window* window;
	Layer* layer;
	Label* fps;
	Sprite* CF;


	float speedX = 0.5f;
	float speedY = 0.5f;

public:
	Game(){}


	void init() override
	{
		window = createWindow("Game", 960, 540, false);
		layer = new Layer(new BatchRenderer2D(), new Shader("src/shaders/basic.vert", "src/shaders/basic.frag"), maths::mat4::othographic(-16, 16, -9.0f, 9.0f, -1.0f, 1.0f));


		CF = new Sprite(-15, 0, 5, 4, "logo.png");

	   fps = new Label("", -15.5f, 7.5f,"mario",42, 0xff0000ff);

	   AudioManager::add(new AudioClip("music", "bg.wav"));
	   AudioManager::get("music")->loop();

		layer->add(new Sprite(0, 0, 32, 18, "logo.png"));
		layer->add(CF);
		layer->add(fps);
	}
	void tick() override
	{
		fps->text = std::to_string(getFPS());

//		speedX *= -1;

		//if(speedX < 0)
		//	CF->scale(vec2(5, 4));

		//if (speedX > 0)
		//	CF->scale(vec2(-5, 4));

	}
	void update() override
	{
	if(Input::GetKey(GLFW_KEY_RIGHT))
	{
		CF->translate(vec3(speedX, 0, 0));
		CF->scale(vec2(-5,4));
	}
	if (Input::GetKey(GLFW_KEY_LEFT))
	{
		CF->translate(vec3(-speedX, 0, 0));		
		CF->scale(vec2(5, 4));

	}
	if (Input::GetKey(GLFW_KEY_UP))
	{
		CF->translate(vec3(0, speedY, 0));
	}
	if (Input::GetKey(GLFW_KEY_DOWN))
	{
		CF->translate(vec3(0, -speedY, 0));
	}
	}
	void render() override
	{
		layer->render();
		AudioManager::update();
	}
};

int main()
{
	Game game;
	game.start();

	return 0;
}