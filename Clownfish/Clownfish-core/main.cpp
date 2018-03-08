#include <iostream>
#include "src\graphics\window.h"
#include "src\input\input.h"


#define LOGLN(x) std::cout << x;
#define LOG(x) std::cout << x << std::endl;

int main()
{

	using namespace clownfish;
	using namespace graphics;
	using namespace input;

	Window window("Rectangle.exe", 800, 600);
	Input input();
	glClearColor(0.2f, 0.9f, 0.8f, 1.0f);




	while (!window.closed())
	{
		window.clear();

		if(Input::isKeyPressed(GLFW_KEY_B))
		{
			LOG("Pressed B");
		}


		if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
		{
			double x, y;
			Input::getMousePosition(x, y);
			LOGLN(x);
			LOGLN(",");
			LOG(y);
		}


		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		
		glEnd();

		window.update();
	}
	return 0;
}
