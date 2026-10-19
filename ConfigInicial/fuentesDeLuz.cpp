//Practica 9
//Reyes Sánchez Laura Pamela
//Fecha de entrega: 18 de octubre de 2026
//No. de cuenta: 318083593

#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SOIL2/SOIL2.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// ==========================================================
// PROTOTIPOS
// ==========================================================

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

// ==========================================================
// VENTANA
// ==========================================================

const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;

int SCREEN_WIDTH;
int SCREEN_HEIGHT;

// ==========================================================
// CÁMARA
// ==========================================================

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

GLfloat lastX = WIDTH / 2.0f;
GLfloat lastY = HEIGHT / 2.0f;

bool keys[1024];
bool firstMouse = true;

// ==========================================================
// LUCES PUNTUALES
// ==========================================================

// La primera luz corresponde a la FOGATA.
// Esta posición permanece FIJA.

glm::vec3 pointLightPositions[] = {
    glm::vec3(0.0f, 0.36f, 0.8f),   // FOGATA
    glm::vec3(0.0f, 0.0f, 0.0f),    // APAGADA
    glm::vec3(0.0f, 0.0f, 0.0f),    // APAGADA
    glm::vec3(0.0f, 0.0f, 0.0f)     // APAGADA
};

// ==========================================================
// VÉRTICES
// ==========================================================

float vertices[] = {
    // BACK
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,

     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,

    // FRONT
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, 0.5f,  0.0f, 0.0f, 1.0f,

     0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,

    // LEFT
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

    // RIGHT
     0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
     0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

     0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
     0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

     // BOTTOM
     -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,

      0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
     -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
     -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

     // TOP
     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,

      0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
     -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
};


GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;


int main()
{
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Previo9 Pamela Reyes", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    glewExperimental = GL_TRUE;

    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

  
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

 
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
    Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");

    // ======================================================
    // MODELOS
    // ======================================================

    Model Dog((char*)"Models/RedDog.obj");
    Model Piso((char*)"Models/piso.obj");
    Model Fire((char*)"Models/FOGATA FOR SKET.obj");
    Model Luna((char*)"Models/Luna.obj");
    Model Lamp((char*)"Models/lamp.obj");

    // ======================================================
    // VAO / VBO
    // ======================================================

    GLuint VBO;
    GLuint VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Posición
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

   
    lightingShader.Use();

    glUniform1i(glGetUniformLocation(lightingShader.Program, "material.difuse"), 0);
    glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);

  
    glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

   
    while (!glfwWindowShouldClose(window))
    {
        
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

       
        glfwPollEvents();
        DoMovement();

        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);

        // ==================================================
        // TRANSPARENCIA
        // ==================================================

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // ==================================================
        // SHADER DE ILUMINACIÓN
        // ==================================================

        lightingShader.Use();

        // ==================================================
        // POSICIÓN DE CÁMARA
        // ==================================================

        glUniform3f(glGetUniformLocation(lightingShader.Program, "viewPos"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        // ==================================================
        // LUNA
        // LUZ DIRECCIONAL
        // ==================================================

        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.08f, 0.08f, 0.10f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.30f, 0.30f, 0.35f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.6f);

        // ==================================================
        // FOGATA
        // LUZ PUNTUAL FIJA
        // ==================================================

        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);

        // Ambient
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.0f, 0.0f, 0.0f);

        // Difusa naranja de la fogata
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 1.0f, 0.25f, 0.03f);

        // Especular
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 0.20f, 0.05f);

        // Atenuación
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);

        // ==================================================
        // POINT LIGHT 1 APAGADA
        // ==================================================

        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.0f, 0.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.0f);

        // ==================================================
        // POINT LIGHT 2 APAGADA
        // ==================================================

        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 0.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.0f);

        // ==================================================
        // POINT LIGHT 3 APAGADA
        // ==================================================

        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 0.0f, 0.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.0f);

        // ==================================================
        // SPOTLIGHT DE LA LÁMPARA
        // ==================================================

        // Posición de la lámpara
        glm::vec3 lampLightPosition = glm::vec3(-0.65f, 0.35f, 0.6f);

        // Punto al que apunta: el perro
        glm::vec3 dogTarget = glm::vec3(0.0f, 0.55f, 0.0f);

        // Dirección del reflector
        glm::vec3 lampDirection = glm::normalize(dogTarget - lampLightPosition);

        // --------------------------------------------------
        // POSICIÓN
        // --------------------------------------------------

        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), lampLightPosition.x, lampLightPosition.y, lampLightPosition.z);

        // --------------------------------------------------
        // DIRECCIÓN
        // --------------------------------------------------

        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), lampDirection.x, lampDirection.y, lampDirection.z);

        // --------------------------------------------------
        // AMBIENTE
        // --------------------------------------------------

        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.02f, 0.02f, 0.01f);

        // --------------------------------------------------
        // DIFUSA
        // LUZ AMARILLA CÁLIDA
        // --------------------------------------------------

        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 1.0f, 0.78f, 0.45f);

        // --------------------------------------------------
        // ESPECULAR
        // --------------------------------------------------

        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 1.0f, 0.85f, 0.60f);

        // --------------------------------------------------
        // ATENUACIÓN
        // --------------------------------------------------

        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.09f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.032f);

        // --------------------------------------------------
        // CONO DEL REFLECTOR
        // --------------------------------------------------

        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(18.0f)));
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(28.0f)));

        // ==================================================
        // MATERIAL
        // ==================================================

        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);

        // ==================================================
        // MATRICES
        // ==================================================

        glm::mat4 view = camera.GetViewMatrix();

        GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
        GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // ==================================================
        // EMISIÓN
        // ==================================================

        glUniform1f(glGetUniformLocation(lightingShader.Program, "emissionStrength"), 0.0f);

        // ==================================================
        // PISO
        // ==================================================

        glm::mat4 model = glm::mat4(1.0f);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Piso.Draw(lightingShader);

        // ==================================================
        // PERRO
        // ==================================================

        model = glm::mat4(1.0f);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Dog.Draw(lightingShader);

        // ==================================================
        // FOGATA
        // ==================================================

        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.2f));
        model = glm::translate(model, glm::vec3(0.0f, 1.8f, 4.0f));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Fire.Draw(lightingShader);

        // ==================================================
        // LÁMPARA
        // ==================================================
       
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.65f, 0.0f, 0.6f));
        model = glm::scale(model, glm::vec3(0.15f));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Lamp.Draw(lightingShader);

        // ==================================================
        // LUNA
        // ==================================================

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.2f, 3.0f, -0.5f));
        model = glm::scale(model, glm::vec3(0.9f));

        // Emisión de la luna
        glUniform1f(glGetUniformLocation(lightingShader.Program, "emissionStrength"), 1.2f);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Luna.Draw(lightingShader);

        // Apagamos la emisión
        glUniform1f(glGetUniformLocation(lightingShader.Program, "emissionStrength"), 0.0f);

        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}


void DoMovement()
{
    // Adelante
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
        camera.ProcessKeyboard(FORWARD, deltaTime);

    // Atrás
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
        camera.ProcessKeyboard(BACKWARD, deltaTime);

    // Izquierda
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
        camera.ProcessKeyboard(LEFT, deltaTime);

    // Derecha
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// ==========================================================
// KEY CALLBACK
// ==========================================================

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // ESC
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
        glfwSetWindowShouldClose(window, GL_TRUE);

    // Teclas
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

// ==========================================================
// MOUSE CALLBACK
// ==========================================================

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}