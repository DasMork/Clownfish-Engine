#include <iostream>
#include "src\graphics\window.h"
#include "src\input\input.h"
#include "src\maths\maths.h"
#include "src\graphics\shader.h"


#define LOGLN(x) std::cout << x;
#define LOG(x) std::cout << x << std::endl;


int main()
{

	using namespace clownfish;
	using namespace graphics;
	using namespace input;
	using namespace maths;

	//INITIALIZATION
	Window window("Rectangle.exe", 800, 600);
	Input input;

	//MAT4 TEST
	mat4 position = mat4::translation(vec3(1,2,5));
	LOG(position);

	//SET BACKGROUND COLOUR
	glClearColor(0.2f, 0.9f, 0.8f, 1.0f);
	
	
	
//SHADER
	GLuint vbo;
	GLfloat vertices[] = 
	{
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	mat4 ortho = mat4::othographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);


	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	glUniformMatrix4fv(glGetUniformLocation(shader.m_ShaderID, "pr_matrix"), 1, GL_FALSE, ortho.elements);






	//UPDATE
	while (!window.closed())
	{
		window.clear();

	
		//INPUTS
		if(input.GetMouseButton(GLFW_MOUSE_BUTTON_1))
		{
			LOG("PRESSED Mouse Button 1");
		}
		if (input.GetMouseButton(GLFW_MOUSE_BUTTON_2))
		{
			LOG("PRESSED Mouse Button 2");
		}


		//DRAWRECTANGLE
		glDrawArrays(GL_TRIANGLES, 0, 6);




		window.update();
	}
	return 0;
}
