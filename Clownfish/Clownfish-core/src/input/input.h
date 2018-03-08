#pragma once


#include <GL\glew.h>
#include <GLFW\glfw3.h>



#define MAX_KEYS 1024
#define MAX_BUTTONS 32

namespace clownfish
{
	namespace input
	{

		class Input
		{
		private:
			static bool m_Keys[MAX_KEYS];
			static bool m_Buttons[MAX_BUTTONS];
			static double mx, my;
			GLFWwindow *m_Window;

		public:

			Input();
			~Input();


			bool isKeyPressed(unsigned int keycode)const;
			bool isMouseButtonPressed(unsigned int keycode) const;
			void getMousePosition(double& x, double& y)const;

		private:
			bool init();
	
		};

	}
}