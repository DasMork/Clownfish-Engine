#include "input.h"
#include <iostream>

namespace clownfish {
	namespace input {


		bool Input::m_Keys[MAX_KEYS];
		bool Input::m_Buttons[MAX_BUTTONS];
		double Input::mx;
		double Input::my;
		GLFWwindow m_Window;


		Input::Input()
		{


			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_Keys[i] = false;
			}
			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				m_Buttons[i] = false;
			}
		}
		Input::~Input() {}

		bool Input::init()
		{

		
		}
	    bool Input::isKeyPressed(unsigned int keycode) const
		{
			if (keycode >= MAX_KEYS)
				return false;

			return m_Keys[keycode];
		}
		bool Input::isMouseButtonPressed(unsigned int keycode)const
		{
			if (keycode >= MAX_BUTTONS)
				return false;

			return m_Buttons[keycode];
		}
		void Input::getMousePosition(double& x, double& y)const
		{
			x = mx;
			y = my;
		}

	}
}