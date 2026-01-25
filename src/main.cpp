// wip simulation of planetary motion about a star
// will hopefully develop into a black hole when I have the computational power for it
// commented every line cause I fucking hate all of you

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace std;

// Callback in case the window's size changes
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main() {

	if (!glfwInit()) return -1; // Initialise GLFW

	// Tell GLFW that 3.3 is the GL version we're using, specifically its core-profile
	// We do this to allow it to make arrangements catered to our specification
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "balls", NULL, NULL);

	// Set its context as the current active one
	glfwMakeContextCurrent(window);

	// Initialise the GLAD loader by passing GLFW's function that knows how to fetch the addresses of OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1;

	// Tell GL our window dimensions and define the coordinate plane it'll use
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	cout << "Running...";

	// Render loop - ensures the program doesn't just draw an image and terminate immediately
	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Safely delete all the resources that were allocated to GLFW
	glfwTerminate();
	return 0;
}