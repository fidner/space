// Experimental simulation of planetary motion about a star

// Involves analysis of orbital error overtime when using different numerical integrators
// including Euler and Runge-Kutta methods as well as extrapolation techniques like Bulirsch-Stoe 

// Tracks orbital paths over elongated periods of time to highlight the changes that occur
// as a result of slightly different initial conditions

// currently in the learning stage of understanding how GL works

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace std;

// Define the necessary shaders to allow drawing

const char* vertexShaderSrc = "#version 330 core\n"
	"layout(location = 0) in vec3 aPos;\n"
	"void main() {\n"
    "	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0"; 

const char* fragShaderSrc = "#version 330 core\n"
	"out vec4 fragColour;\n"
	"void main() {\n"
	"	fragColour = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

// Callback in case the window's size changes
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// Self-explanatory
// Will eventually include movement keys and maybe a toggle for integration methods
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() {

	if (!glfwInit()) return -1; // Initialise GLFW

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "balls", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// Initialise the GLAD loader by passing GLFW's function that knows how to fetch the addresses of OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1;

	// Not particularly necessary
	glViewport(0, 0, 800, 600);

	// A set of 3D vertices that we intend to draw
	// These set of vectors form a simple triangle
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	// Declare a buffer object to store vertices in the GPU (faster read-writes)
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Declare Vertex Shader to help GL determine vertex positions
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShader);

	// Checks if compilation was successful --
	int success;
	char errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cout << "Vertex shader compilation failed" << errorLog << std::endl;
	}
	// --

	// Declare Fragment Shader to determine each pixel's colour as vertices are mapped onto the window
	unsigned int fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
	glCompileShader(fragShader);

	// Checks if compilation was successful --
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragShader, 512, NULL, errorLog);
		std::cout << "Fragment shader compilation failed" << errorLog << std::endl;
	}
	// --

	// Link our two shaders
	unsigned int shader;
	shader = glCreateProgram();
	glAttachShader(shader, vertexShader);
	glAttachShader(shader, fragShader);
	glLinkProgram(shader);
	
	// Checks if link was successful --
	glGetProgramiv(shader, GL_LINK_STATUS, &success);

	if (!success) {
    	glGetProgramInfoLog(shader, 512, NULL, errorLog);
	}
	// -- 

	// Activate the linked shader and get rid of the old ones
	glUseProgram(shader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	// Tells GL how to interpret vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	// -----------
	// UNFINISHED - need to bind VAO
	// -----------

	// Render loop
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		// rendering here

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Safely delete all the resources that were allocated to GLFW and terminate
	glfwTerminate();
	return 0;
}