#pragma once


#include <GL\glew.h>
#include <GLFW\glfw3.h>





namespace clownfish
{
	namespace input
	{

		static class Input
		{
		private:

		public:
			static bool m_Keys[GLFW_KEY_LAST];
			static bool m_Buttons[GLFW_MOUSE_BUTTON_LAST];
			static double mx, my;
			static bool m_KeyState[GLFW_KEY_LAST];
			static bool m_KeyTyped[GLFW_KEY_LAST];
			static bool m_MouseState[GLFW_MOUSE_BUTTON_LAST];
			static bool m_MouseClicked[GLFW_MOUSE_BUTTON_LAST];
			Input();
			~Input();

			static bool GetKey(unsigned int keycode);
			static bool GetKeyDown(unsigned int keycode);

			static bool GetMouseButton(unsigned int keycode);
			static bool GetMouseButtonDown(unsigned int keycode);

			static void GetMousePosition(double& x, double& y);

		private:
		//	bool init();
	
		};

	}
}