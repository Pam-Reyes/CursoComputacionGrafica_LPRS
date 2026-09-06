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
		-0.7f, -0.9f, 0.0f,   1.0f,1.0f,0.0f, //0 
		-0.6f, -0.88f, 0.0f,   1.0f,1.0f,0.0f, //1
		-0.48f, -0.8f, 0.0f,   1.0f,1.0f,0.0f,//2
		-0.35f, -0.75f, 0.0f,   1.0f,1.0f,0.0f,//3
		-0.25f, -0.45f, 0.0f,   1.0f,1.0f,0.0f,//4
		-0.1f, -0.6f, 0.0f,   1.0f,1.0f,0.0f,//5
		
		0.05f, -0.58f, 0.0f,    1.0f,1.0f,0.0f,//6
		0.2f, -0.55f, 0.0f,    1.0f,1.0f,0.0f,//7
		0.4f, -0.25f, 0.0f,    1.0f,1.0f,0.0f,//8
		
		0.35f,  0.1f, 0.0f,    1.0f,1.0f,0.0f, //9
		0.25f,  0.45f, 0.0f,    1.0f,1.0f,0.0f,//10
		0.0f,  0.7f, 0.0f,    1.0f,1.0f,0.0f,//11

		-0.3f,  0.7f, 0.0f,    1.0f,1.0f,0.0f, //12
		-0.55f,  0.5f, 0.0f,    1.0f,1.0f,0.0f, //13
		-0.65f,  0.2f, 0.0f,    1.0f,1.0f,0.0f,//14
		-0.75f,  0.05f, 0.0f,    1.0f,1.0f,0.0f,//15

		-0.7f,  -0.15f, 0.0f,    1.0f,1.0f,0.0f,//16
		-0.78f,  -0.2f, 0.0f,    1.0f,1.0f,0.0f,//17
		-0.76f,  -0.38f, 0.0f,    1.0f,1.0f,0.0f,//18
		-0.74f,  -0.5f, 0.0f,    1.0f,1.0f,0.0f,//19
		-0.7f,  -0.61f, 0.0f,    1.0f,1.0f,0.0f,//20

		//vertices interiores
		-0.38f,  0.40f, 0.0f,   1.0f,1.0f,1.0f, //21
		-0.20f,  0.28f, 0.0f,   1.0f,1.0f,1.0f, //22
		 0.05f,  0.25f, 0.0f,   1.0f,1.0f,1.0f, //23
		 0.22f,  0.18f, 0.0f,   1.0f,1.0f,1.0f, //24
		
		-0.52f,  0.18f, 0.0f,   1.0f,1.0f,1.0f, //25
		-0.34f,  0.08f, 0.0f,   1.0f,1.0f,1.0f, //26
		-0.10f,  0.08f, 0.0f,   1.0f,1.0f,1.0f, //27
		 0.12f,  0.02f, 0.0f,   1.0f,1.0f,1.0f, //28
		 0.28f, -0.02f, 0.0f,   1.0f,1.0f,1.0f, //29

		-0.62f, -0.02f, 0.0f,   1.0f,1.0f,1.0f, //30
		-0.42f, -0.12f, 0.0f,   1.0f,1.0f,1.0f, //31
		-0.20f, -0.12f, 0.0f,   1.0f,1.0f,1.0f, //32
		 0.00f, -0.18f, 0.0f,   1.0f,1.0f,1.0f, //33
		 0.20f, -0.18f, 0.0f,   1.0f,1.0f,1.0f, //34

		-0.68f, -0.30f, 0.0f,   1.0f,1.0f,1.0f, //35
		-0.50f, -0.28f, 0.0f,   1.0f,1.0f,1.0f, //36
		-0.32f, -0.30f, 0.0f,   1.0f,1.0f,1.0f, //37
		-0.12f, -0.35f, 0.0f,   1.0f,1.0f,1.0f, //38
		 0.10f, -0.35f, 0.0f,   1.0f,1.0f,1.0f, //39

		-0.62f, -0.45f, 0.0f,   1.0f,1.0f,1.0f, //40
		-0.42f, -0.48f, 0.0f,   1.0f,1.0f,1.0f, //41
		-0.25f, -0.50f, 0.0f,   1.0f,1.0f,1.0f, //42

		-0.62f, -0.62f, 0.0f,   1.0f,1.0f,1.0f, //43
		-0.48f, -0.65f, 0.0f,   1.0f,1.0f,1.0f, //44
		-0.35f, -0.65f, 0.0f,   1.0f,1.0f,1.0f, //45
	};
	unsigned int indices[] = {  
		// Parte superior
		   20, 0, 1,
		   20, 1, 2,
		   20, 2, 3,
		   20, 3, 4,

		   4, 5, 6,
		   4, 6, 38,
		   4, 38, 37,

		   5, 38, 39,
		   5, 39, 6,

		   6, 39, 7,
		   7, 39, 34,
		   7, 34, 8,

		   8, 34, 29,
		   8, 29, 9,

		   9, 29, 24,
		   9, 24, 10,

		   10, 24, 23,
		   10, 23, 11,

		   11, 23, 22,
		   11, 22, 12,

		   12, 22, 21,
		   12, 21, 13,

		   13, 21, 25,
		   13, 25, 14,

		   14, 25, 30,
		   14, 30, 15,

		   // Parte central izquierda
		   21, 22, 26,
		   21, 26, 25,

		   22, 23, 27,
		   22, 27, 26,

		   23, 24, 28,
		   23, 28, 27,

		   24, 29, 28,

		   27, 28, 33,
		   27, 33, 32,
		   27, 32, 26,

		   26, 32, 31,
		   26, 31, 30,
		   26, 30, 25,

		   28, 29, 34,
		   28, 34, 33,

		   29, 34, 8,

		   // Parte central inferior
		   30, 31, 36,
		   30, 36, 35,
		   30, 35, 16,
		   30, 16, 15,

		   31, 32, 37,
		   31, 37, 36,

		   32, 33, 38,
		   32, 38, 37,

		   33, 34, 39,
		   33, 39, 38,

		   // Parte inferior
		   35, 36, 40,
		   35, 40, 18,
		   35, 18, 17,
		   35, 17, 16,

		   36, 37, 41,
		   36, 41, 40,

		   37, 38, 41,

		   38, 39, 6,

		   40, 41, 43,
		   40, 43, 20,
		   40, 20, 19,

		   41, 44, 43,
		   41, 45, 44,

		   43, 44, 2,
		   43, 2, 1,
		   43, 1, 0,
		   43, 0, 20,

		   44, 45, 3,
		   44, 3, 2,

		   45, 4, 3

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


		//glPointSize(3);
		//glDrawArrays(GL_POINTS, 0, 45);
		//glDrawArrays(GL_LINE_LOOP, 0, 21);//dibujar contorno

		//glDrawArrays(GL_LINES, 0, 45);
		//glDrawArrays(GL_LINE_LOOP,0,45);

		//glDrawArrays(GL_TRIANGLES, 0, 45);
		//glDrawElements(GL_TRIANGLES, 45,GL_UNSIGNED_INT,0);


		glPointSize(3);

		glDrawArrays(GL_POINTS, 0, 45);

		// Contorno del cráneo
		glDrawArrays(GL_LINE_LOOP, 0, 21);

		// Triángulos
		glDrawElements(GL_TRIANGLES,
			sizeof(indices) / sizeof(unsigned int),
			GL_UNSIGNED_INT,
			0);
		
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