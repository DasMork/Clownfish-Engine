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
	/*	bool m_Keys[GLFW_KEY_LAST];
		bool m_Buttons[GLFW_MOUSE_BUTTON_LAST];
		double mx;
		double my;*/

	public:
		Window(const char *m_title, int m_width, int m_height);
		~Window();
		bool closed() const;
		void clear() const;
		void update() ;


		int getWidth() { return m_Width; }
		int getHeight() { return m_Height; }

	private:
		bool init();
		void LoadStandardFonts();
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		friend static void window_resize(GLFWwindow *window, int width, int height);

	};


}
}