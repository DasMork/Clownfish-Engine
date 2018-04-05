#include "..\src\clownfish.h"


using namespace clownfish;
using namespace graphics;
using namespace input;
using namespace maths;
using namespace audio;

class Mario : public Clownfish
{

private:
	Window* window;
	Sprite* mario;
	Layer* layer;
	Label* fps;
	Label* ups;
	BatchRenderer2D* renderer;
public:
	Mario() {}

	// On Begin
	void init() override
	{
		window = createWindow("Game", 960, 540, false);
		renderer = new BatchRenderer2D;
		layer = new Layer(renderer, new Shader("src/shaders/basic.vert", "src/shaders/basic.frag"), maths::mat4::othographic(-16, 16, -9.0f, 9.0f, -1.0f, 1.0f));


		fps = new Label("5000", -15.5f, 7.5f, "arial", 42, 0xff0000ff);
		ups = new Label("60", 14.0f, 7.5f, "arial", 42, 0xff0000ff);
		mario = new Sprite(0, 0, 5, 4, "test.png");


		layer->add(mario);
		layer->add(fps);
		layer->add(ups);

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
			mario->scale(vec2(-10, 8));

		if (x < -0.1f)
			mario->scale(vec2(10,8));

		mario->translate(vec3(x * 0.5f, y * 0.5f, 0));


	}

	//As fast as possible
	void render() override
	{
		glClearColor(0, 0, 0.8f, 1);
		layer->render();
		AudioManager::update();
	}
	
};


//Game
int main()
{
	Mario game;
	game.start();
	return 0;
}

