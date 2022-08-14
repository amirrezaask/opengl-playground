#define GLEW_STATIC
#define GLFW_INCLUDE_NONE

#include "iostream"

#include <GLFW/glfw3.h>
#include "GL/glew.h"


int main() {
	std::cout << "Hello world" << std::endl;
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

	glGenBuffers(6 * sizeof(float), &buffer_idx);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_idx);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);

	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
	
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}