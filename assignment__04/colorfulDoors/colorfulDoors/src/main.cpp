
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<fstream>
#include "global.h"
#include "renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "VertexArray.h"

#include "Shader.h"
#include "texture.h"



#include "assets/libraries/imgui/imgui.h"
#include "assets/libraries/imgui/imgui_impl_glfw_gl3.h"

using namespace std;



const float WINDOW_WIDTH = 960;
const float WINDOW_HEIGHT = 540;

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
	


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

	/*
	0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, -0.5f, -0.5f, -0.0f,
	*/
	float positions[] = {		//colors
		 -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
		  0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
		  0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
		 -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,

		 -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
		  0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
		  0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
		 -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
	};



	unsigned int indices[] = {

		//FRONT
		0, 1, 3,
		3, 2, 1,

		//BACK
		4, 5, 7,
		7, 6, 5,

		//RIGHT
		1, 5, 2,
		2, 6, 5,

		//LEFT
		0, 4, 3,
		3, 7, 4,

		//TOP
		3, 2, 7,
		7, 6, 2,

		//BOTTOM
		0, 1, 4,
		4, 5, 1,


	};



	GLC(glEnable(GL_BLEND));
	GLC(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	

	VertexBuffer vb(positions, sizeof(positions));

	IndexBuffer ib(indices, sizeof(indices)/sizeof(*indices));

	VertexArray va;
	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(2);
	va.addBuffer(vb, layout);




	Shader shader("src/shaders/vertex.shader", "src/shaders/fragment.shader");

	shader.bind();

	shader.setUniform4f("u_color", 0.5, 0.3, 0.5, 1);


	//glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	glm::mat4 proj;
	proj = glm::perspective(glm::radians(45.0f), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3));

	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	


	glm::mat4 mvp = proj * view * model;

	shader.setUniformMat4f("m_mvp", mvp);
	

	Renderer renderer;

	

	Texture texture("src/assets/textures/container.jpg");
	texture.bind();
	shader.setUniform1i("u_texture", 0);


	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	// Setup style
	ImGui::StyleColorsDark();


	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	glm::vec3 transA(0, 0, 0);
	float deg = 55;


	glm::vec3 transB(0, 0, 0);

	glEnable(GL_DEPTH_TEST);



	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//renderer.draw(va, ib, shader);

		ImGui_ImplGlfwGL3_NewFrame();

		
		model = glm::rotate(glm::mat4(1.0f), glm::radians(deg), transA);
		model = translate(glm::mat4(1.0f), transB);

		mvp = proj * view * model;

		shader.setUniformMat4f("m_mvp", mvp);

		renderer.draw(va, ib, shader);

		
		
		//glDrawArrays(GL_TRIANGLES, 0, numOpPositions/2);


		//GLC(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));



		// 1. Show a simple window.
		{

			ImGui::SliderFloat3("trans A", &transA.x, -1.0f, 1.0f);
			ImGui::SliderFloat3("trans B", &transB.x, -1, 1);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}



		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		/* Swap front and back buffers */
		GLC(glfwSwapBuffers(window));

		/* Poll for and process events */
		GLC(glfwPollEvents());
	}

	// Cleanup
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}