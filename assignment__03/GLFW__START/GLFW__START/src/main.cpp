#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>

using namespace std;

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		cout << "Error: GLEW INIT\n";

	cout << glGetString(GL_VERSION) << endl;

	float positions[6] = {
		 0.0f,  0.5f,
		 0.5f, -0.5f,
		-0.5f, -0.5f
	};


	unsigned int buffer;
	// give ID to our buffer
	glGenBuffers(1, &buffer);
	//select that buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//add data to my buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions) * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);



		glDrawArrays(GL_TRIANGLES, 0, sizeof(positions));


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}