#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<fstream>
#include<math.h>

#define PI acos(-1)

const float WINDOW_WIDTH = 700;
const float WINDOW_HEIGHT = 700;


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
void drawCircle(float arr[], int sz, float r, float x, float y) {

	for (int i = 0; i < sz; i += 2) {
		arr[i] = r * cos(2 * PI*(i / (sz*1.0))) + x;
		arr[i + 1] = r * sin(2 * PI*(i / (sz * 1.0))) + y;
	}
	
}
int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(2);

	if (glewInit() != GLEW_OK)
		cout << "Error: GLEW INIT\n";

	cout << glGetString(GL_VERSION) << endl;



	float r = 1.0, rSpeed = 0.02;
	float g = 0.0, gSpeed = 0.03;
	float b = 0.0, bSpeed = 0.01;
	float radius = 0.2;
	float x = 0.0, xSpeed = 0.02;
	float y = 0.0, ySpeed = 0.03;


	float positions[720];

	drawCircle(positions, (sizeof(positions) / sizeof(*positions)), radius, x, y);

	/*for (int i = 0; i < 720; i++) {
		cout << "positions[" << i << "] = " << positions[i] << endl;
	}*/


	int numOpPositions = (sizeof(positions) / sizeof(*positions));

	unsigned int buffer;
	// give ID to our buffer
	glGenBuffers(1, &buffer);
	//select that buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//add data to my buffer
	glBufferData(GL_ARRAY_BUFFER, numOpPositions * sizeof(float), positions, GL_DYNAMIC_DRAW);



	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);




	string vertexShader = readShader("src/shaders/vertex.shader");

	string fragmentShader = readShader("src/shaders/fragment.shader");


	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);


	int u_color__loc = glGetUniformLocation(shader, "u_color");

	//ASSERT(u_color__loc != -1);
	cout << "u_color__loc " << u_color__loc << endl;
	

	

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		drawCircle(positions, (sizeof(positions) / sizeof(*positions)), radius, x, y);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glUniform4f(u_color__loc, r, 0.3, 0.5, 0.5);

		glDrawArrays(GL_POLYGON, 0, numOpPositions/2);

		if (r > 1 || r < 0)
			rSpeed *= -1;

		if (g > 1 || g < 0)
			gSpeed *= -1;

		if (b > 1 || b < 0)
			bSpeed *= -1;

		if (x + radius >= 1 || x - radius <= -1)
			xSpeed *= -1;

		if (y + radius >= 1 || y - radius <= -1)
			ySpeed *= -1;

		r += rSpeed;
		g += rSpeed;
		b += rSpeed;

		x += xSpeed;
		y += ySpeed;


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}