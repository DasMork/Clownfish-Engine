#include "..\src\clownfish.h"


using namespace clownfish;
using namespace graphics;
using namespace input;
using namespace maths;
using namespace audio;

class DailyFun : public Clownfish
{

private:
	Window* window;
	Label* fps;
	Layer* layer;



public:
	DailyFun() {}


	void init() override
	{
		window = createWindow("DailyFun", 320, 480, false);

		fps = new Label("", -8.5f, 13.5f, "Freedoka", 42, 0xff0000ff);
		layer = new Layer(new BatchRenderer2D(), new Shader("src/shaders/basic.vert", "src/shaders/basic.frag"), maths::mat4::othographic(-9, 9, -16.0f, 16.0f, -1.0f, 1.0f));
		AudioManager::add(new AudioClip("music", "DailyFun.wav"));
		AudioManager::get("music")->loop();

		layer->add(new Sprite(0, 0, 18, 32, "giphy.png"));
		layer->add(fps);
	}

	// Once per Second
	void tick() override
	{
		fps->text = std::to_string(getFPS());

	}


	//60 Times per Second
	void update() override
	{
	
	}

	//As fast as possible
	void render() override
	{
		layer->render();
		AudioManager::update();
	}
};


//Game
int main()
{
	DailyFun game;
	game.start();

	return 0;
}