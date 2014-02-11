// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include <vector>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
using namespace std;

#include <common/shader.hpp>
/*
GLfloat *circle(GLfloat xpos, GLfloat ypos, GLfloat r)
{


	return vertexBuffer;
}*/

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	if (!glfwOpenWindow(1024, 1024, 0, 0, 0, 0, 32, 0, GLFW_WINDOW))
	{
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetWindowTitle("Tutorial 02");

	// Ensure we can capture the escape key being pressed below
	glfwEnable(GLFW_STICKY_KEYS);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint VertexArrayID2;
	glGenVertexArrays(1, &VertexArrayID2);
	glBindVertexArray(VertexArrayID2);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	//Initialice first buffer
	GLfloat r = 0.1f;
	GLfloat xpos = -0.5f;
	GLfloat ypos = 0.0f;
	GLfloat ang = 0.0f;
	int index = 0;
	GLfloat step = 0.1f; //same decimals for even size of g_vertex_buffer_data[int]
	GLfloat pi = 3.1f;

	GLfloat g_vertex_buffer_data[3 * 2 * 31 + 1]; //((2.0f * pi) / step)

	do{
		g_vertex_buffer_data[index] = r*cos(ang) + xpos;
		index = index + 1;
		g_vertex_buffer_data[index] = r*sin(ang) + ypos;
		index = index + 1;
		g_vertex_buffer_data[index] = 0.0f;
		ang = ang + step;
		//cout << " v:" << ang;
		index = index + 1;
	} while (ang <= (2 * 3 * pi));

	g_vertex_buffer_data[3 * 2 * 31 + 1] = r + xpos;
	g_vertex_buffer_data[3 * 2 * 31 + 2] = 0.0f + ypos;
	g_vertex_buffer_data[3 * 2 * 31 + 3] = 0.0f;
	//end

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	//Initialice first buffer
	GLfloat r2 = 0.1f;
	GLfloat xpos2 = +0.5f;
	GLfloat ypos2 = 0.0f;
	GLfloat ang2 = 0.0f;
	int index2 = 0;
	GLfloat step2 = 0.1f; //same decimals for even size of g_vertex_buffer_data[int]

	GLfloat g_vertex_buffer_data2[3 * 2 * 31 + 1]; //((2.0f * pi) / step)

	do{
		g_vertex_buffer_data2[index2] = r2*cos(ang2) + xpos2;
		index = index + 1;
		g_vertex_buffer_data2[index2] = r2*sin(ang2) + ypos2;
		index = index + 1;
		g_vertex_buffer_data2[index2] = 0.0f;
		ang2 = ang2 + step2;
		//cout << " v:" << ang;
		index = index2 + 1;
	} while (ang2 <= (2 * 3 * pi));

	g_vertex_buffer_data2[3 * 2 * 31 + 1] = r2 + xpos2;
	g_vertex_buffer_data2[3 * 2 * 31 + 2] = 0.0f + ypos2;
	g_vertex_buffer_data2[3 * 2 * 31 + 3] = 0.0f;
	//end

	GLuint vertexbuffer2;
	glGenBuffers(2, &vertexbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data2), g_vertex_buffer_data2, GL_STATIC_DRAW);

	do{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		//Draw circle!
		
		glDrawArrays(GL_TRIANGLE_FAN, 0, 314); //314 Vertices
		
		// 2nd attribute buffer : vertices
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			2,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		//Draw circle!

		glDrawArrays(GL_TRIANGLE_FAN, 0, 314); //314 Vertices

		// Draw the triangle !
		//glDrawArrays(GL_TRIANGLES, 0, 3); //3 indices starting at 0 -> 1 triangle
		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS &&
	glfwGetWindowParam(GLFW_OPENED));

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);

	glDeleteBuffers(1, &vertexbuffer2);
	glDeleteVertexArrays(1, &VertexArrayID2);

	return 0;
}