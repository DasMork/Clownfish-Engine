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


			bool GetKey(unsigned int keycode)const;
			bool GetKeyDown(unsigned int keycode)const;

			bool GetMouseButton(unsigned int keycode) const;
			bool GetMouseButtonDown(unsigned int keycode) const;

			void GetMousePosition(double& x, double& y)const;

		private:
		//	bool init();
	
		};

	}
}