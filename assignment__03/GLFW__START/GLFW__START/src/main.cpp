#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<string>

#include<fstream>


using namespace std;

static unsigned int CompileShader(unsigned int type, const string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);


	// Error 
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		cout << "Failed to compile " << ((type == GL_VERTEX_SHADER) ? "vertex" : "fragment") << endl;
		cout << message << endl;
		glDeleteShader(id);

		return 0;
	}

	return id;
}

static unsigned int CreateShader(const string& vertexShader, const string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;


}

string readShader(string filePath)
{
	ifstream t(filePath);
	string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

	return str;
}

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

	float positions[] = {
		 -0.5f, -0.5f,
		  0.5f, -0.5f,
		  0.5f, 0.5f,
		 -0.5f, 0.5f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	int numOpPositions = (sizeof(positions) / sizeof(*positions));

	unsigned int buffer;
	// give ID to our buffer
	glGenBuffers(1, &buffer);
	//select that buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//add data to my buffer
	glBufferData(GL_ARRAY_BUFFER, numOpPositions * sizeof(float), positions, GL_STATIC_DRAW);



	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);



	// index buffer object
	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);




	string vertexShader = readShader("src/shaders/vertex.shader");

	string fragmentShader = readShader("src/shaders/fragment.shader");


	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);



		//glDrawArrays(GL_TRIANGLES, 0, numOpPositions/2);

		glDrawElements(GL_TRIANGLES, (sizeof(indices) / sizeof(*indices)), GL_UNSIGNED_INT, nullptr);


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}