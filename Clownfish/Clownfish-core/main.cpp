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

#define LOGLN(x) std::cout << x;
#define LOG(x) std::cout << x << std::endl;

#define CUBE 0
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

	float jump = 0.01;

	GLint texIDs[] = 
	{ 
		0,1,2,3,4,5,6,7,8,9

	};


	//SHADER
	shader.enable();
	shader.setUniform1iv("textures", texIDs, 10);
	


	 

#if CUBE
	//3DRENDERER
	float rotation = 0;
	Simple3DRenderer renderer3d;
	Model Test(vec3(0, 0, 0), 2, vec4(1, 0, 1, 1), shader);
#elif !LOGO 
	for (float y = -9; y < 9.0f; y++)
	{
		for (float x = -16; x < 16.0f; x++)
		{

			//layer.add(new Sprite(x, y, 0.9f, 0.9f, maths::vec4(1, rand() % 1000 / 1000.0f, 0, 1)));

		}

	}
	Sprite* Logo = new Sprite(-8, -6.0f,1, 1, "mario.png");
	//Sprite* Kira = new Sprite(0, 0, 2, 2, "kira.png");


	layer.add(new Sprite(-16, -9, 268, 18, "1-1.png"));
	//layer.add(new Sprite(-7, 0 , 4, 6, "lantern.png"));
	//layer.add(new Sprite(0, 0, 4, 4, "cube.png"));

	layer.add(Logo);
	float x = 16;
	float x1 = -16;
#endif
	//UPDATE
	while (!window.closed())
	{
		window.clear();
		mat4 ortho = mat4::othographic(x1, x, -9.0f, 9.0f, -1.0f, 1.0f);
		shader.setUniformMat4("pr_matrix", ortho);

		if(input.GetKey(GLFW_KEY_D))
		{
		x += 0.1f;
		x1 += 0.1f;
		}

		if (input.GetKey(GLFW_KEY_A))
		{
			x -= 0.1f;
			x1 -= 0.1f;
	}


#if CUBE
		//CUBE
		glClearColor(1, 1, 1, 1);
		rotation++;
		//shader.setUniformMat4("ml_matrix", mat4::rotation(rotation / 100, vec3(0, 1, 0)) * mat4::rotation(30, (vec3(1, 0, 0))));
		double a, b;
		input.GetMousePosition(a, b);
		if (input.GetMouseButton(GLFW_MOUSE_BUTTON_1))
		{
			shader.setUniformMat4("ml_matrix", mat4::rotation(a, vec3(0, 1, 0))* mat4::rotation(b, vec3(1, 0, 0)));
		}
		renderer3d.submit(&Test);
		renderer3d.flush();
#endif
		
#if LIGHTTOMOUSE
		//LIGHT TO MOUSE
		double x, y;
		input.GetMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f-16), (float)(9.0f - y * 18.0f / 540)));

#endif
		Logo->translate(vec3(0, jump, 0));

		layer.render();
		window.update();
		fps++;
		if (time.elapsed() - timer > 1.0f)
		{
			jump = -jump;
			timer += 1.0f;
			printf("%d FPS\n", fps);
			fps = 0;
		}
	}
	return 0;
}