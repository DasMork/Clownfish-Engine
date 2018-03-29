#include "window.h"
#include "..\input\input.h"
#include <iostream>
#include "fontmanager.h"

namespace clownfish {
	namespace graphics {





		Window::Window(const char *title, int width, int height)
		{
			m_Title = title;
			m_Width = width;
			m_Height = height;

			if (!init())
				glfwTerminate();



		}
		Window::~Window()
		{
			glfwTerminate();
		}

		bool Window::init()
		{
			if (!glfwInit())
			{
				std::cout << "Failed to initialize GFLW!" << std::endl;
				return false;
			}
			else
				std::cout << "Initialized GLFW!" << std::endl;


			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);


			if (!m_Window)
			{
				std::cout << "Failed to create GLFW Window!" << std::endl;
				return false;
			}
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetFramebufferSizeCallback(m_Window, window_resize);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);

			glfwSwapInterval(0);

			if (glewInit() != GLEW_OK)
			{
				std::cout << "Could not intialize GLEW!" << std::endl;
				return false;
			}
			else
				std::cout << "Initialized GLEW!" << std::endl;


			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			LoadStandardFonts();

			return true;
		}




		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update()
		{
			for (int i = 0; i < GLFW_KEY_LAST; i++)
				input::Input::m_KeyTyped[i] = input::Input::m_Keys[i] && !input::Input::m_KeyState[i];

			for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
				input::Input::m_MouseClicked[i] = input::Input::m_Buttons[i] && !input::Input::m_MouseState[i];

			memcpy(input::Input::m_KeyState, input::Input::m_Keys, GLFW_KEY_LAST);
			memcpy(input::Input::m_MouseState, input::Input::m_Buttons, GLFW_MOUSE_BUTTON_LAST);


			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;


			glfwSwapBuffers(m_Window);
			glfwPollEvents();

		}
		bool  Window::closed() const
		{
			return glfwWindowShouldClose(m_Window) == 1;
		}

		void window_resize(GLFWwindow *window, int width, int height)
		{
			glViewport(0, 0, width, height);
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Width = width;
			win->m_Height = height;
		}


		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			input::Input::m_Keys[key] = action == GLFW_PRESS;


		}
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);

			input::Input::m_Buttons[button] = action != GLFW_RELEASE;


		}
		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			input::Input::mx = xpos;
			input::Input::my = ypos;

		}

		void Window::LoadStandardFonts()
		{
			FontManager::add(new Font("arial", "arial.ttf", 30));
			FontManager::add(new Font("mario", "mario.ttf", 30));

		}

	}
}