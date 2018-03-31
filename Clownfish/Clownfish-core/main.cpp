
#if 0

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
#include "src\graphics\sprite.h"
#include "src\graphics\static_sprite.h"
#include "src\graphics\layers\group.h"
#include "tilelayer.h"
#include "src\graphics\texture.h"
#include "src\graphics\label.h"

#include "src\graphics\fontmanager.h"
#include "src\audio\audiomanager.h"


#define LOGLN(x) std::cout << x;
#define LOG(x) std::cout << x << std::endl;

#define LIGHTTOMOUSE 0


int main()
{

	using namespace clownfish;
	using namespace graphics;
	using namespace input;
	using namespace maths;
	using namespace audio;

	//INITIALIZATION
	Window window("Clownfish-Launcher", 960, 540);

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

	AudioManager::add(new AudioClip("test", "bg.wav"));
	AudioManager::add(new AudioClip("sound", "sound.wav"));

	AudioManager::get("test")->loop();

	Group group(mat4::translation(vec3(0, 0, 0)));
	for (float y = -9; y < 9.0f; y++)
	{
		for (float x = -16; x < 16.0f; x++)
		{


			//layer.add(new Sprite(x, y, 0.9f, 0.9f, 0xffffff));

		}
		Sprite* Mario = new Sprite(-8, 10.7f, 1, 1.1f, "mario.png");
		Label* fpstext = new Label("Fps: ", -15, 7, 0xffffffff);
		Label* coinText = new Label("Coins: ", 10, 7, "mario", 0xffffffff);

		Sprite* Background = new Sprite(116, 0, 268, 18, "1-1.png");

		layer.add(Background);
		layer.add(fpstext);
		layer.add(coinText);
		layer.add(Mario);

		float cameraPosition = 0;
		float jumpStart = 0;
		bool isJumping = false;
		bool groundcheck = false;
		//UPDATE
		while (!window.closed())
		{
			window.clear();


			
			if (Input::GetKeyDown(GLFW_KEY_P))
			{
				AudioManager::get("test")->pause();
			}	
			if (Input::GetKeyDown(GLFW_KEY_R))
			{
				AudioManager::get("test")->resume();
			}
	
		


			mat4 ortho = mat4::othographic(cameraPosition - 16, cameraPosition + 16, -9.0f, 9.0f, -1.0f, 1.0f);
			shader.setUniformMat4("pr_matrix", ortho);
			coinText->position = vec3(cameraPosition + 10, 7, 0);
			fpstext->position = vec3(cameraPosition - 15, 7, 0);

			if (Mario->getPosition().x - cameraPosition > 5)
			{
				cameraPosition += 0.1f;
			}
			if (Mario->getPosition().x - cameraPosition < -8)
			{
				cameraPosition -= 0.1f;
			}
			if (Mario->getPosition().y > -6.1f && !isJumping)
			{
				Mario->translate(vec3(0, -0.002f, 0));
				groundcheck = false;
			}
			else
			{
				groundcheck = true;
			}


			if (Input::GetKey(GLFW_KEY_D) || Input::GetKey(GLFW_KEY_RIGHT))
			{
				Mario->translate(vec3(playerSpeed, 0, 0));
				Mario->scale(vec2(1, Mario->getSize().y));

				/*	x += 0.004f;
					x1 += 0.004f;*/
			}

			if (Input::GetKey(GLFW_KEY_A) || Input::GetKey(GLFW_KEY_LEFT))
			{
				Mario->translate(vec3(-playerSpeed, 0, 0));
				Mario->scale(vec2(-1, Mario->getSize().y));

				/*x -= 0.004f;
				x1 -= 0.004f;*/
		}
			if (Input::GetKeyDown(GLFW_KEY_SPACE) && groundcheck)
			{
				isJumping = true;
				groundcheck = false;
				jumpStart = Mario->getPosition().y;

				if(AudioManager::get("sound")->isPlaying())
					AudioManager::get("sound")->stop();

				AudioManager::get("sound")->play();
			}
			if (isJumping)
			{
				Mario->translate(vec3(0, 0.003f, 0));
				if (Mario->getPosition().y - jumpStart > 5)
					isJumping = false;
			}



#if LIGHTTOMOUSE
			//LIGHT TO MOUSE
			double x, y;
			input.GetMousePosition(x, y);
			shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / window.getWidth() - 16), (float)(9.0f - y * 18.0f / window.getHeight())));

#endif
			layer.render();
			AudioManager::update();
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
		return 0;
}
}
#endif
