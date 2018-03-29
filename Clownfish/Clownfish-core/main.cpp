#include <iostream>
#include <vector>
#include <time.h>

#include "src\utils\timer.h"
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

#include "src\graphics\Renderable3D.h"
#include "src\graphics\simple3drenderer.h"
#include "src\graphics\sprite.h"
#include "src\graphics\static_sprite.h"
#include "src\graphics\layers\tilelayer.h"
#include "src\graphics\layers\group.h"
#include "src\graphics\texture.h"
#include "src\graphics\label.h"

#include "src\graphics\fontmanager.h"

#define LOGLN(x) std::cout << x;
#define LOG(x) std::cout << x << std::endl;

#define LIGHTTOMOUSE 0



int main()
{

	using namespace clownfish;
	using namespace graphics;
	using namespace input;
	using namespace maths;

	//INITIALIZATION
	Window window("Clownfish-Launcher", 960, 540);
	Input input;
	Timer time;
	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	TileLayer layer(&shader);




	BatchRenderer2D renderer;
	std::vector<Renderable2D*> sprites;

	//FPS
	float timer = 0;
	unsigned int fps = 0;


	float playerSpeed = 0.001f;
	float jump = 0.01;
	float MoveX = 0;

	GLint texIDs[] =
	{
		0,1,2,3,4,5,6,7,8,9
	};


	//SHADER
	shader.enable();
	shader.setUniform1iv("textures", texIDs, 10);
	mat4 ortho = mat4::othographic(-16, 16, -9.0f, 9.0f, -1.0f, 1.0f);
	shader.setUniformMat4("pr_matrix", ortho);

	for (float y = -9; y < 9.0f; y++)
	{
		for (float x = -16; x < 16.0f; x++)
		{

			//layer.add(new Sprite(x, y, 0.9f, 0.9f, maths::vec4(1, rand() % 1000 / 1000.0f, 0, 1)));

		}
		Sprite* Mario = new Sprite(-8, 10.7f, 1, 1.1f, "mario.png");
		Label* fpstext = new Label("Fps: ", -15, 7,"arial", 0xffffffff);
		Label* coinText = new Label("Coins: ", 10, 7, "mario", 0xffffffff);

		Sprite* Background = new Sprite(-16, -9, 268, 18, "1-1.png");

		layer.add(Background);
		layer.add(fpstext);
		layer.add(coinText);
		layer.add(Mario);

		float x = 16;
		float x1 = -16;

		//UPDATE
		while (!window.closed())
		{
			window.clear();

			
			if (Mario->getPosition().y > -6.7f)
			{
				Mario->translate(vec3(0, -0.004f, 0));

			}
		

			if (input.GetKey(GLFW_KEY_D) || input.GetKey(GLFW_KEY_RIGHT))
			{
				Mario->translate(vec3(playerSpeed, 0, 0));
				/*	x += 0.004f;
					x1 += 0.004f;*/
			}

			if (input.GetKey(GLFW_KEY_A) || input.GetKey(GLFW_KEY_LEFT))
			{
				Mario->translate(vec3(-playerSpeed, 0, 0));
				/*x -= 0.004f;
				x1 -= 0.004f;*/
			}
			if (input.GetKeyDown(GLFW_KEY_SPACE))
			{
				Mario->translate(vec3(0, 5, 0));
			}

#if LIGHTTOMOUSE
			//LIGHT TO MOUSE
			double x, y;
			input.GetMousePosition(x, y);
			shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / window.getWidth() - 16), (float)(9.0f - y * 18.0f / window.getHeight())));

#endif
			layer.render();
			window.update();
			fps++;
			if (time.elapsed() - timer > 1.0f)
			{
				fpstext->text = "Fps: " + std::to_string(fps);
				jump = -jump;
				timer += 1.0f;
				printf("%d FPS\n", fps);
				fps = 0;
			}
		}
		FontManager::clean();
		return 0;
	}
}