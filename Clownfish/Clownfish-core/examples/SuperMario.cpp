#include "..\src\clownfish.h"


#define LEVELLENGTH 1

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

	Sprite* ground;
	Sprite* wall;
	bool facingRight = true;
public:
	Mario() {}

	// On Begin
	void init() override
	{
		window = createWindow("Game", 960, 540, false);
		renderer = new BatchRenderer2D;
		layer = new Layer(renderer, new Shader("src/shaders/basic.vert", "src/shaders/basic.frag"), maths::mat4::othographic(-16, 16, -9.0f, 9.0f, -1.0f, 1.0f));


		fps = new Label("5000", -15.5f, 7.5f, "mario", 42, 0xff0000ff);
		ups = new Label("60", 14.0f, 7.5f, "mario", 42, 0xff0000ff);
		mario = new Sprite(-5, 3, 1.5f, 1.5f, "examples/Mario/mario.png");
		wall = new Sprite(-5, -5.55f, 3, 3, "examples/Mario/pipe.png");


		Group* background = new Group(mat4::translation(vec3(0, 0, 0)));	
		for (int i = 0; i < LEVELLENGTH * 32; i += 32)
		{
			background->add(new Sprite(i, 1, 32, 22, "examples/Mario/background.png"));
		}

		wall->setColision(true);
		mario->setColision(true);

		layer->add(background);
		layer->add(wall);
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
		Controls();
		

	}

	//As fast as possible
	void render() override
	{
		if (Input::GetKeyDown(KEY_SPACE))
		{
			mario->translate(vec3(0, 5, 0));
		}

		glClearColor(0, 0, 0.8f, 1);
		layer->render();
		AudioManager::update();
	}


	void Controls()
	{
		float x = Input::GetAxis(HORIZONTAL);
		float y = Input::GetAxis(VERTICAL);

		if (x > 0.1f && !facingRight)
		{
			facingRight = true;
			mario->scale(vec2(mario->getSize().x * -1, mario->getSize().y));
		}

		if (x < -0.1f && facingRight)
		{
			facingRight = false;
			mario->scale(vec2(mario->getSize().x * -1, mario->getSize().y));
		}
		float gravity = 0;

		if (mario->getPosition().y > -6.49f)
		{
			 gravity = -0.25;
		}
	
		mario->translate(vec3(x * 0.2f, gravity, 0));
	


	}
	
};


//Game
int main()
{
	Mario game;
	game.start();
	return 0;
}

