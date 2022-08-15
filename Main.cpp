#define GLEW_STATIC
#define GLFW_INCLUDE_NONE

#include "iostream"

#include <GLFW/glfw3.h>
#include "GL/glew.h"

unsigned int CompileShader(unsigned int type, const std::string& src) {
	auto shaderId = glCreateShader(type);
	const char* CSrc = src.c_str();
	glShaderSource(shaderId, 1, &CSrc, nullptr);
	glCompileShader(shaderId);

	/*int result;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {

	}*/
	return shaderId;

}


unsigned int CreateShader(std::string& vertexShader, std::string& pixelShader) {
	auto program = glCreateProgram();
	auto vertexShaderId = CompileShader(GL_VERTEX_SHADER, vertexShader);
	auto pixelShaderId = CompileShader(GL_FRAGMENT_SHADER, pixelShader);

	glAttachShader(program, vertexShaderId);
	glAttachShader(program, pixelShaderId);
	glLinkProgram(program);
	glValidateProgram(program);

	return program;
}

int main() {
	if (glfwInit() == GLFW_FALSE) std::cout << "Cannot init glfw" << std::endl;
	auto window = glfwCreateWindow(1600, 900, "Hello World", NULL, NULL);
	if (!window) std::cout << "Cannot create window" << std::endl;
	glfwMakeContextCurrent(window);


	if (glewInit() != GLEW_OK) std::cout << "Cannot init glew" << std::endl;
	

	unsigned int buffer_idx;
	float vertices[6] = {
		-0.5f, 0.0f, // position of each vertex
		0.0f, -0.5f,
		0.0f, 0.5f,
	};

	glGenBuffers(1, &buffer_idx);
	
	glBindBuffer(GL_ARRAY_BUFFER, buffer_idx);
	
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	std::string vertexShader = 
		"#version 330 core"
		"\n"
		"layout(location = 0) in vec4 position;"
		"\n"
		"void main() {\n"
		"gl_Position = position;\n"
		"}\n"
		;
	std::string pixelShader = 
		"#version 330 core"
		"\n"
		"layout(location = 0) out vec4 color;"
		"\n"
		"void main() {\n"
		"color = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n"
		;
	auto shader = CreateShader(vertexShader, pixelShader);
	glUseProgram(shader);

	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
	
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glDeleteProgram(shader);

	glfwTerminate();
	return 0;
}
