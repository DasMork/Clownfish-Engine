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

		public:
			static bool m_Keys[MAX_KEYS];
			static bool m_Buttons[MAX_BUTTONS];
			static double mx, my;

			Input();
			~Input();


			bool GetKey(unsigned int keycode)const;

			bool GetMouseButton(unsigned int keycode) const;
			void GetMousePosition(double& x, double& y)const;

		private:
		//	bool init();
	
		};

	}
}