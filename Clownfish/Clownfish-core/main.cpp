#include <iostream>
#include "src\graphics\window.h"
#include "src\input\input.h"
#include "src\maths\maths.h"
#include "src\graphics\shader.h"
#include "src\graphics\buffers\buffer.h"
#include "src\graphics\buffers\indexbuffer.h"
#include "src\graphics\buffers/vertextarray.h"


#include "src\graphics\Renderable2D.h"
#include "src\graphics\simple2drenderer.h"


#define LOGLN(x) std::cout << x;
#define LOG(x) std::cout << x << std::endl;


int main()
{

	using namespace clownfish;
	using namespace graphics;
	using namespace input;
	using namespace maths;

	//INITIALIZATION
	Window window("Clownfish-Launcher", 960, 540);
	Input input;
	Simple2DRenderer renderer;


	//SHADER
	mat4 ortho = mat4::othographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);



	//RENDERER
	Renderable2D sprite(maths::vec3(0, 0, 0), maths::vec2(20, 10), maths::vec4(1, 0.5f, 0, 1), shader);



	//UPDATE
	while (!window.closed())
	{
		window.clear();


		//LIGHT TO MOUSE
		double x, y;
		input.GetMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540)));



		//SET BACKGROUND COLOUR
		glClearColor(1, 1, 1, 1.0f);

		//INPUTS
		if (input.GetMouseButton(GLFW_MOUSE_BUTTON_1))
		{

			LOG("PRESSED Mouse Button 1");
		
		}
		if (input.GetMouseButton(GLFW_MOUSE_BUTTON_2))
		{
			LOG("PRESSED Mouse Button 2");

		}


		//RENDERER
		renderer.submit(&sprite);
		renderer.flush();


		window.update();
	}
	return 0;
}