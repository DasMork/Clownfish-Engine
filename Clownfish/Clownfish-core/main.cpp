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

#include "src\utils\timer.h"

#define LOGLN(x) std::cout << x;
#define LOG(x) std::cout << x << std::endl;

#define BATCH_RENDERER 1
#define PONG_GAME 1


int main()
{

	using namespace clownfish;
	using namespace graphics;
	using namespace input;
	using namespace maths;

	//INITIALIZATION
	Window window("Clownfish-Launcher", 960, 540);
	Input input;
	Timer time, deltaTime;

	float timer = 0;
	unsigned int fps = 0;

	//SHADER
	mat4 ortho = mat4::othographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);

	//PONG
	float x1 = 0, y1 = 2.5f, x2 = 15, y2 = 2.5f;
	float Bx = 7.5f, By = 4;
	float playerSpeed = 0.7f;
	float ballSpeedX = 0.7f, ballSpeedY = 0.7f;
	bool bounced = false, endGame = false;
	int P1Score = 0, P2Score = 0;

	Sprite P11(2, 8, 0.25f, 2, vec4(0, 0, 0, 1));
	Sprite P12(4, 8, 0.25f, 2, vec4(0, 0, 0, 1));
	Sprite P13(6, 8, 0.25f, 2, vec4(0, 0, 0, 1));

	Sprite P21(9, 8, 0.25f, 2, vec4(0, 0, 0, 1));
	Sprite P22(11, 8, 0.25f, 2, vec4(0, 0, 0, 1));
	Sprite P23(13, 8, 0.25f, 2, vec4(0, 0, 0, 1));



	std::vector<Renderable2D*> sprites;
	//srand(time(NULL));

#if BATCH_RENDERER 

	//RENDERER
	BatchRenderer2D renderer;

	for (float y = 0; y < 9.0f; y += 0.05f)
	{
		for (float x = 0; x < 16.0f; x += 0.05f)
		{
			sprites.push_back(new Sprite(x, y, 0.04f, 0.04f, maths::vec4(1, rand() % 1000 / 1000.0f, 0, 1)));

		}

	}
#else
	//RENDERER
	StaticSprite sprite(0, 1, 20, 10, maths::vec4(1, 0.5f, 1, 1), shader);
	StaticSprite sprite2(0, 0, 20, 1, maths::vec4(0, 0, 1, 1), shader);
	Simple2DRenderer renderer;
	for (float y = 0; y < 9.0f; y += 0.05f)
	{
		for (float x = 0; x < 16.0f; x += 0.05f)
		{
			sprites.push_back(new StaticSprite(x, y, 0.04f, 0.04f, maths::vec4(1, rand() % 1000 / 1000.0f, 0, 1), shader));

		}

	}
#endif

	//UPDATE
	while (!window.closed())
	{
		deltaTime.reset();
		window.clear();



		//LIGHT TO MOUSE
		double x, y;
		input.GetMousePosition(x, y);



		Sprite P1(0, y1, 1, 4, vec4(0, 0, 1, 1));
		Sprite P2(15, y2, 1, 4, vec4(0, 0, 1, 1));
		Sprite Ball(Bx, By, 1, 1, vec4(1, 1, 1, 1));



		//SET BACKGROUND COLOUR
		glClearColor(0, 0, 0, 1);

#if PONG_GAME

		shader.setUniform2f("light_pos", vec2(Bx + 0.5f, By + 0.5f));

		//PONG
		if (input.GetKey(GLFW_KEY_SPACE) && endGame) {
			endGame = false;
			P1Score = 0;
			P2Score = 0;
		}
		if (!endGame)
		{

			if (input.GetKey(GLFW_KEY_W))
			{
				if (y1 < 5)
					y1 += playerSpeed * 0.05f;
			}
			if (input.GetKey(GLFW_KEY_S))
			{
				if (y1 > 0)
					y1 -= playerSpeed * 0.05f;

			}
			if (input.GetKey(GLFW_KEY_UP))
			{
				if (y2 < 5)
					y2 += playerSpeed * 0.05f;
			}
			if (input.GetKey(GLFW_KEY_DOWN))
			{
				if (y2 > 0)
					y2 -= playerSpeed * 0.05f;

			}


			if (Bx < 12 && Bx > 3)
				bounced = false;

			if (By > 8)
				ballSpeedY = -ballSpeedY;

			if (By < 0)
				ballSpeedY = -ballSpeedY;

			if (Bx < 1 && By > y1 && By + 0.5f < y1 + 4 && !bounced)
			{
				if (Bx < 0.8f)
					ballSpeedY = -ballSpeedY;

				ballSpeedX = -ballSpeedX;
				ballSpeedX *= 1.1f;
				ballSpeedY *= 1.1f;
				bounced = true;
			}

			if (Bx > 14 && By > y2 && By < y2 + 0.5f + 4 && !bounced)
			{
				ballSpeedX = -ballSpeedX;

				if (Bx > 14.2f)
					ballSpeedY = -ballSpeedY;

				ballSpeedX *= 1.1f;
				ballSpeedY *= 1.1f;

				bounced = true;
			}


			if (Bx < -1)
			{
				Bx = 7.5f;
				By = 4;
				ballSpeedX = 0.7f;
				ballSpeedY = 0.7f;
				ballSpeedX = -ballSpeedX;
				P2Score += 1;


			}
			if (Bx > 16)
			{
				Bx = 7.5f;
				By = 4;
				ballSpeedX = 0.7f;
				ballSpeedY = 0.7f;
				ballSpeedX = -ballSpeedX;
				P1Score += 1;

			}


			By += ballSpeedY*0.01f;
			Bx += ballSpeedX*0.01f;


			}
#else

		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540)));

#endif

#if BATCH_RENDERER

		//RENDERER
		renderer.begin();

		for (int i = 0; i < sprites.size(); i++)
		{
			renderer.submit(sprites[i]);
		}
#if PONG_GAME
		renderer.submit(&P1);
		renderer.submit(&P2);
		renderer.submit(&Ball);
		if (P1Score >= 1)
		{
			renderer.submit(&P11);
		}
		if (P1Score >= 2)
		{
			renderer.submit(&P12);
		}
		if (P1Score >= 3)
		{
			renderer.submit(&P13);
			endGame = true;


		}

		if (P2Score >= 1)
		{
			renderer.submit(&P21);
		}
		if (P2Score >= 2)
		{
			renderer.submit(&P22);
		}
		if (P2Score >= 3)
		{
			renderer.submit(&P23);
			endGame = true;

		}
#endif
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
		fps++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("%d FPS\n", fps);
			fps = 0;
		}




		}
	return 0;
		}