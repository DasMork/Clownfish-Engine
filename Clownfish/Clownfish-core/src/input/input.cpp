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
		const float* Input::m_Axes;
	    int Input::m_ControllerConnected;


		Input::Input()
		{
		
		}
		Input::~Input() {}

		void Input::init()
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

		void Input::update()
		{
			m_ControllerConnected = glfwJoystickPresent(GLFW_JOYSTICK_1);
			if (!m_ControllerConnected)
				return;
			
				int count;
				m_Axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
			

		}

		float Input::GetAxis(int axis) 
		{
			float result = 0;

			if(m_Axes!= nullptr)
			result = m_Axes[axis];

			if(axis == 0)
			{
			if (GetKey(KEY_RIGHT) || GetKey(KEY_D))
				result = 1;

			if (GetKey(KEY_LEFT) || GetKey(KEY_A))
				result = -1;
			}
			if (axis == 1)
			{
				if (GetKey(KEY_UP) || GetKey(KEY_W))
					result = 1;

				if (GetKey(KEY_DOWN) || GetKey(KEY_S))
					result = -1;
			}

		
			return result;
		}


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