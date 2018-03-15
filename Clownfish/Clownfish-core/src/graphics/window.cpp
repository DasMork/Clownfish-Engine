#include "window.h"
#include "..\input\input.h"
#include <iostream>

namespace clownfish {
	namespace graphics {

	
		void window_resize(GLFWwindow *window, int width, int height);



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
			glfwSetWindowSizeCallback(m_Window, window_resize);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);

			glfwSwapInterval(0);

			if(glewInit() != GLEW_OK)
			{
				std::cout << "Could not intialize GLEW!" << std::endl;
				return false;
			}
			else
				std::cout << "Initialized GLEW!" << std::endl;

			
			return true;
		}




		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update() 
		{
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


	}
}