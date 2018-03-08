#pragma once


#include <GL\glew.h>
#include <GLFW\glfw3.h>




namespace clownfish
{
namespace graphics
{

	class Window
	{
	public: 
		GLFWwindow *m_Window;

	private:
		const char *m_Title;
		int m_Width, m_Height;
		bool m_Closed;



	public:
		Window(const char *m_title, int m_width, int m_height);
		~Window();
		bool closed() const;
		void clear() const;
		void update() ;




	private:
		bool init();
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	};


}
}