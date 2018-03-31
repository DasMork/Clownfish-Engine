#include "input.h"
#include <iostream>

namespace clownfish {
	namespace input {


		bool Input::m_Keys[GLFW_KEY_LAST];
		bool Input::m_Buttons[GLFW_MOUSE_BUTTON_LAST];
		double Input::mx;
		double Input::my;
		bool Input::m_KeyState[GLFW_KEY_LAST];
		bool Input::m_KeyTyped[GLFW_KEY_LAST];
		bool Input::m_MouseState[GLFW_MOUSE_BUTTON_LAST];
		bool Input::m_MouseClicked[GLFW_MOUSE_BUTTON_LAST];
		Input::Input()
		{
			for (int i = 0; i < GLFW_KEY_LAST; i++)
			{
				m_Keys[i] = false;
				m_KeyState[i] = false;
				m_KeyTyped[i] = false;
			}
			for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
			{
				m_Buttons[i] = false;
				m_MouseState[i] = false;
				m_MouseClicked[i] = false;
			}
		}
		Input::~Input() {}

		bool Input::GetKey(unsigned int keycode)
		{
			if (keycode >= GLFW_KEY_LAST)
				return false;

			return m_Keys[keycode];
		}


		bool Input::GetKeyDown(unsigned int keycode) 
		{
			if (keycode >= GLFW_KEY_LAST)
				return false;

			return m_KeyTyped[keycode];
		}
		bool Input::GetMouseButton(unsigned int keycode)
		{
			if (keycode >= GLFW_MOUSE_BUTTON_LAST)
				return false;

			return m_Buttons[keycode];
		}
		bool Input::GetMouseButtonDown(unsigned int keycode)
		{

			if (keycode >= GLFW_MOUSE_BUTTON_LAST)
				return false;

			return m_MouseClicked[keycode];
		}
		void Input::GetMousePosition(double& x, double& y)
		{
			x = mx;
			y = my;
		}

	}
}