//Practica #2
//Reyes Sanchez Laura Pamela
//Fecha de entrega: 30 de agosto de 2026
//No. de cuenta: 318083593

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica2 Pamela Reyes", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);

	//Verificaci�n de errores de creacion  ventana
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

	Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
	//haciendo el mapa completo de los vertices en mi imagen
		//contorno del craneo 
		//empezando por el punto mas bajo y de ahi hacia la derecha
		-0.7f, -0.9f, 0.0f,   1.0f,1.0f,0.0f, //1 
		-0.6f, -0.88f, 0.0f,   1.0f,1.0f,0.0f, //2
		-0.48f, -0.8f, 0.0f,   1.0f,1.0f,0.0f,//3
		-0.35f, -0.75f, 0.0f,   1.0f,1.0f,0.0f,//4
		-0.25f, -0.45f, 0.0f,   1.0f,1.0f,0.0f,//5
		-0.1f, -0.6f, 0.0f,   1.0f,1.0f,0.0f,//6
		
		0.05f, -0.58f, 0.0f,    1.0f,1.0f,0.0f,//7
		0.2f, -0.55f, 0.0f,    1.0f,1.0f,0.0f,//8
		0.4f, -0.25f, 0.0f,    1.0f,1.0f,0.0f,//9
		
		0.35f,  0.1f, 0.0f,    1.0f,1.0f,0.0f, //10
		0.25f,  0.45f, 0.0f,    1.0f,1.0f,0.0f,//11
		0.0f,  0.7f, 0.0f,    1.0f,1.0f,0.0f,//12

		-0.3f,  0.7f, 0.0f,    1.0f,1.0f,0.0f, //13
		-0.55f,  0.5f, 0.0f,    1.0f,1.0f,0.0f, //14
		-0.65f,  0.2f, 0.0f,    1.0f,1.0f,0.0f,//15
		-0.75f,  0.05f, 0.0f,    1.0f,1.0f,0.0f,//16

		-0.7f,  -0.15f, 0.0f,    1.0f,1.0f,0.0f,//17
		-0.78f,  -0.2f, 0.0f,    1.0f,1.0f,0.0f,//18
		-0.76f,  -0.38f, 0.0f,    1.0f,1.0f,0.0f,//19
		-0.74f,  -0.5f, 0.0f,    1.0f,1.0f,0.0f,//20
		-0.7f,  -0.61f, 0.0f,    1.0f,1.0f,0.0f,//21

		//vertices interiores
		-0.38f,  0.40f, 0.0f,   1.0f,1.0f,1.0f, //25
		-0.20f,  0.28f, 0.0f,   1.0f,1.0f,1.0f, //26
		 0.05f,  0.25f, 0.0f,   1.0f,1.0f,1.0f, //27
		 0.22f,  0.18f, 0.0f,   1.0f,1.0f,1.0f, //28

		-0.52f,  0.18f, 0.0f,   1.0f,1.0f,1.0f, //29
		-0.34f,  0.08f, 0.0f,   1.0f,1.0f,1.0f, //30
		-0.10f,  0.08f, 0.0f,   1.0f,1.0f,1.0f, //31
		 0.12f,  0.02f, 0.0f,   1.0f,1.0f,1.0f, //32
		 0.28f, -0.02f, 0.0f,   1.0f,1.0f,1.0f, //33

		-0.62f, -0.02f, 0.0f,   1.0f,1.0f,1.0f, //34
		-0.42f, -0.12f, 0.0f,   1.0f,1.0f,1.0f, //35
		-0.20f, -0.12f, 0.0f,   1.0f,1.0f,1.0f, //36
		 0.00f, -0.18f, 0.0f,   1.0f,1.0f,1.0f, //37
		 0.20f, -0.18f, 0.0f,   1.0f,1.0f,1.0f, //38

		-0.68f, -0.30f, 0.0f,   1.0f,1.0f,1.0f, //39
		-0.50f, -0.28f, 0.0f,   1.0f,1.0f,1.0f, //40
		-0.32f, -0.30f, 0.0f,   1.0f,1.0f,1.0f, //41
		-0.12f, -0.35f, 0.0f,   1.0f,1.0f,1.0f, //42
		 0.10f, -0.35f, 0.0f,   1.0f,1.0f,1.0f, //43

		-0.62f, -0.45f, 0.0f,   1.0f,1.0f,1.0f, //44
		-0.42f, -0.48f, 0.0f,   1.0f,1.0f,1.0f, //45
		-0.25f, -0.50f, 0.0f,   1.0f,1.0f,1.0f, //46

		-0.62f, -0.62f, 0.0f,   1.0f,1.0f,1.0f, //47
		-0.48f, -0.65f, 0.0f,   1.0f,1.0f,1.0f, //48
		-0.35f, -0.65f, 0.0f,   1.0f,1.0f,1.0f, //49
	};
	unsigned int indices[] = {  // note that we start from 0!
		// Parte superior
		12, 21, 11,
		11, 21, 22,
		21, 24, 22,
		22, 24, 25,

		// Parte superior izquierda
		12, 24, 13,
		24, 25, 13,
		25, 28, 13,

		// Zona superior central
		22, 23, 24,
		23, 26, 24,
		24, 26, 25,

		// Zona central
		25, 26, 29,
		26, 30, 29,
		26, 27, 30,
		27, 31, 30,

		// Parte derecha superior
		10, 32, 9,
		9, 32, 33,
		10, 27, 32,
		10, 11, 27,
		11, 23, 27,

		// Parte derecha central
		27, 28, 32,
		28, 33, 32,
		28, 10, 27,

		// Parte central inferior
		30, 35, 36,
		30, 29, 35,
		29, 34, 35,
		34, 16, 17,
		34, 17, 35,

		// Parte inferior central
		35, 40, 41,
		35, 41, 36,
		36, 41, 42,
		36, 42, 37,

		// Parte derecha inferior
		37, 42, 43,
		37, 43, 38,
		38, 43, 9,
		38, 33, 9

	};



	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)



	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glBindVertexArray(VAO);


		glPointSize(3);
		glDrawArrays(GL_POINTS, 0, 21);

		//glDrawArrays(GL_LINES, 0, 49);
		glDrawArrays(GL_LINE_LOOP,0,21);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}