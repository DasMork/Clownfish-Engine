#include <iostream>
#include <vector>
#include <time.h>


#include "src\graphics\window.h"
#include "src\input\input.h"
#include "src\maths\maths.h"
#include "src\graphics\shader.h"
#include "src\graphics\buffers\buffer.h"
#include "src\graphics\buffers\indexbuffer.h"
#include "src\graphics\buffers/vertextarray.h"

#include "src\graphics\Renderable2D.h"
#include "src\graphics\simple2drenderer.h"
#include "src\graphics\BatchRenderer2D.h"

#include "src\graphics\sprite.h"
#include "src\graphics\static_sprite.h"


#define LOGLN(x) std::cout << x;
#define LOG(x) std::cout << x << std::endl;

#define BATCH_RENDERER 1

int main()
{

	using namespace clownfish;
	using namespace graphics;
	using namespace input;
	using namespace maths;

	//INITIALIZATION
	Window window("Clownfish-Launcher", 960, 540);
	Input input;


	//SHADER
	mat4 ortho = mat4::othographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);

	std::vector<Renderable2D*> sprites;
	//srand(time(NULL));

#if BATCH_RENDERER
	//RENDERER

	BatchRenderer2D renderer;

	for (float y = 0; y < 9.0f; y+= 0.05f)
	{
		for (float x = 0; x < 16.0f; x+=0.05f)
		{
			sprites.push_back(new Sprite(x, y, 0.04f, 0.04f, maths::vec4(1, rand() % 1000 / 1000.0f, 0, 1)));

		}

	}
#else
	//RENDERER
	StaticSprite sprite(0, 1, 20, 10, maths::vec4(1, 0.5f, 1, 1), shader);
	StaticSprite sprite2(0, 0, 20, 1, maths::vec4(0, 0, 1, 1), shader);
	Simple2DRenderer renderer;
	for (float y = 0; y < 9.0f; y+=0.05f)
	{
		for (float x = 0; x < 16.0f; x+=0.05f)
		{
			sprites.push_back(new StaticSprite(x, y, 0.04f, 0.04f, maths::vec4(1, rand() % 1000 / 1000.0f, 0,  1), shader));

		}

	}
#endif

	//UPDATE
	while (!window.closed())
	{
		window.clear();



		//LIGHT TO MOUSE
		double x, y;
		input.GetMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540)));



		//SET BACKGROUND COLOUR
		glClearColor(0, 0, 0, 1);

		//INPUTS
		if (input.GetMouseButton(GLFW_MOUSE_BUTTON_1))
		{
			LOG("PRESSED Mouse Button 1");
		}
		if (input.GetMouseButton(GLFW_MOUSE_BUTTON_2))
		{
			LOG("PRESSED Mouse Button 2");
		}

#if BATCH_RENDERER

		//RENDERER
		renderer.begin();

		for (int i = 0; i < sprites.size(); i++)
		{
			renderer.submit(sprites[i]);
		}

		renderer.end();
		renderer.flush();
#else
		//RENDERER
		for (int i = 0; i < sprites.size(); i++)
		{

			renderer.submit(sprites[i]);
		}

		renderer.flush();
#endif 



		window.update();
	}
	return 0;
}