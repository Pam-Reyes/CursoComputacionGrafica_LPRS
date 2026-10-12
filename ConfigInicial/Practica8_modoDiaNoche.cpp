//Practica 8
//Reyes Sánchez Laura Pamela
//Fecha de entrega: 7 de octubre de 2026
//No. de cuenta: 318083593


// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();


// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

bool keys[1024];

GLfloat lastX = 400;
GLfloat lastY = 300;

bool firstMouse = true;


// ---------------------------------------------------------
// LIGHT ATTRIBUTES
// ---------------------------------------------------------

// SOL
glm::vec3 lightPos(0.0f, 1.8f, 0.0f);

// LUNA
glm::vec3 lightPos2(0.0f, -1.8f, 0.0f);


// ---------------------------------------------------------
// ANIMATION
// ---------------------------------------------------------

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

float rot = 0.0f;

bool activanim = false;


// ---------------------------------------------------------
// MAIN
// ---------------------------------------------------------

int main()
{
    // Init GLFW
    glfwInit();

    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object
    GLFWwindow* window = glfwCreateWindow(
        WIDTH,
        HEIGHT,
        "Previo 8 Pamela Reyes",
        nullptr,
        nullptr
    );

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(
        window,
        &SCREEN_WIDTH,
        &SCREEN_HEIGHT
    );

    // Set the required callback functions
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // GLFW Options
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set this to true so GLEW knows to use a modern approach
    glewExperimental = GL_TRUE;

    // Initialize GLEW
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;

        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // OpenGL options
    glEnable(GL_DEPTH_TEST);


    // ---------------------------------------------------------
    // SHADERS
    // ---------------------------------------------------------

    Shader shader(
        "Shader/modelLoading.vs",
        "Shader/modelLoading.frag"
    );

    Shader lampshader(
        "Shader/lamp.vs",
        "Shader/lamp.frag"
    );

    Shader lightingShader(
        "Shader/lighting.vs",
        "Shader/lighting.frag"
    );


    // ---------------------------------------------------------
    // LOAD MODEL
    // ---------------------------------------------------------

    // SOLO UTILIZAMOS EL RED DOG
    Model dog((char*)"Models/RedDog.obj");

    glm::mat4 projection = glm::perspective(
        camera.GetZoom(),
        (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
        0.1f,
        100.0f
    );


    // ---------------------------------------------------------
    // VERTICES DE LAS LÁMPARAS
    // ---------------------------------------------------------

    float vertices[] = {

        // Back face
        -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,

         0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,

        // Front face
        -0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,

         0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,

        // Left face
        -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,

        // Right face
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,

         0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,

         // Bottom face
         -0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,
          0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,
          0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,

          0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,
         -0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,
         -0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,

         // Top face
         -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
          0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
          0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,

          0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
         -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
         -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f
    };


    // ---------------------------------------------------------
    // VAO Y VBO
    // ---------------------------------------------------------

    GLuint VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    // Position
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    // Normal
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glEnableVertexAttribArray(1);

    glBindVertexArray(0);


    // ---------------------------------------------------------
    // GAME LOOP
    // ---------------------------------------------------------

    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();

        deltaTime = currentFrame - lastFrame;

        lastFrame = currentFrame;


        // Check and call events
        glfwPollEvents();

        DoMovement();


        // ---------------------------------------------------------
        // ANIMACIÓN DE LAS LUCES
        // ---------------------------------------------------------

        if (activanim)
        {
            rot += deltaTime * 0.15f;
        }


        // Distancia de las luces al perro
        float radio = 1.0f;


        // ---------------------------------------------------------
        // POSICIÓN DEL SOL
        // ---------------------------------------------------------

        lightPos.x = radio * cos(rot);
        lightPos.y = radio * sin(rot);
        lightPos.z = 0.0f;


        // ---------------------------------------------------------
        // POSICIÓN DE LA LUNA
        // Está exactamente al lado contrario del Sol
        // ---------------------------------------------------------

        lightPos2.x =
            radio * cos(rot + glm::radians(180.0f));

        lightPos2.y =
            radio * sin(rot + glm::radians(180.0f));

        lightPos2.z = 0.0f;


        // ---------------------------------------------------------
        // CLEAR
        // ---------------------------------------------------------

        glClearColor(
            0.05f,
            0.05f,
            0.08f,
            1.0f
        );

        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );


        // ---------------------------------------------------------
        // LIGHTING SHADER
        // ---------------------------------------------------------

        lightingShader.Use();


        // ---------------------------------------------------------
        // POSICIÓN DEL SOL
        // ---------------------------------------------------------

        GLint lightPosLoc =
            glGetUniformLocation(
                lightingShader.Program,
                "light.position"
            );

        glUniform3f(
            lightPosLoc,
            lightPos.x,
            lightPos.y,
            lightPos.z
        );


        // ---------------------------------------------------------
        // POSICIÓN DE LA CÁMARA
        // ---------------------------------------------------------

        GLint viewPosLoc =
            glGetUniformLocation(
                lightingShader.Program,
                "viewPos"
            );

        glUniform3f(
            viewPosLoc,
            camera.GetPosition().x,
            camera.GetPosition().y,
            camera.GetPosition().z
        );


        // ---------------------------------------------------------
        // FACTORES DÍA / NOCHE
        // ---------------------------------------------------------

        float sunFactor =
            (sin(rot) + 1.0f) / 2.0f;

        float moonFactor =
            1.0f - sunFactor;


        // ---------------------------------------------------------
        // SOL
        // Luz cálida 
        // ---------------------------------------------------------

        // Ambiente
        glUniform3f(
            glGetUniformLocation(
                lightingShader.Program,
                "light.ambient"
            ),
            0.18f * sunFactor,
            0.08f * sunFactor,
            0.02f * sunFactor
        );


        // Difusa
        glUniform3f(
            glGetUniformLocation(
                lightingShader.Program,
                "light.diffuse"
            ),
            1.4f * sunFactor,
            0.55f * sunFactor,
            0.08f * sunFactor
        );


        // Especular
        glUniform3f(
            glGetUniformLocation(
                lightingShader.Program,
                "light.specular"
            ),
            1.2f * sunFactor,
            0.55f * sunFactor,
            0.15f * sunFactor
        );


        // ---------------------------------------------------------
        // LUNA
        // Luz fría azulada
        // ---------------------------------------------------------

        // Posición
        glUniform3f(
            glGetUniformLocation(
                lightingShader.Program,
                "light2.position"
            ),
            lightPos2.x,
            lightPos2.y,
            lightPos2.z
        );


        // Ambiente
        glUniform3f(
            glGetUniformLocation(
                lightingShader.Program,
                "light2.ambient"
            ),
            0.015f * moonFactor,
            0.025f * moonFactor,
            0.07f * moonFactor
        );


        // Difusa
        glUniform3f(
            glGetUniformLocation(
                lightingShader.Program,
                "light2.diffuse"
            ),
            0.20f * moonFactor,
            0.35f * moonFactor,
            0.75f * moonFactor
        );


        // Especular
        glUniform3f(
            glGetUniformLocation(
                lightingShader.Program,
                "light2.specular"
            ),
            0.30f * moonFactor,
            0.45f * moonFactor,
            0.90f * moonFactor
        );


        // ---------------------------------------------------------
        // MATRICES
        // ---------------------------------------------------------

        glm::mat4 view =
            camera.GetViewMatrix();


        glUniformMatrix4fv(
            glGetUniformLocation(
                lightingShader.Program,
                "projection"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );


        glUniformMatrix4fv(
            glGetUniformLocation(
                lightingShader.Program,
                "view"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(view)
        );


        // ---------------------------------------------------------
        // MATERIAL
        // ---------------------------------------------------------

        glUniform3f(
            glGetUniformLocation(
                lightingShader.Program,
                "material.ambient"
            ),
            0.5f,
            0.5f,
            0.5f
        );


        glUniform3f(
            glGetUniformLocation(
                lightingShader.Program,
                "material.diffuse"
            ),
            0.8f,
            0.8f,
            0.8f
        );


        glUniform3f(
            glGetUniformLocation(
                lightingShader.Program,
                "material.specular"
            ),
            1.0f,
            1.0f,
            1.0f
        );


        glUniform1f(
            glGetUniformLocation(
                lightingShader.Program,
                "material.shininess"
            ),
            32.0f
        );


        // ---------------------------------------------------------
        // DIBUJAR RED DOG
        // ---------------------------------------------------------

        glm::mat4 model(1.0f);


        glUniformMatrix4fv(
            glGetUniformLocation(
                lightingShader.Program,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );


        dog.Draw(lightingShader);


        // ---------------------------------------------------------
        // DIBUJAR LAS FUENTES DE LUZ
        // ---------------------------------------------------------

        lampshader.Use();


        glUniformMatrix4fv(
            glGetUniformLocation(
                lampshader.Program,
                "projection"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );


        glUniformMatrix4fv(
            glGetUniformLocation(
                lampshader.Program,
                "view"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(view)
        );


        // ---------------------------------------------------------
        // SOL
        // ---------------------------------------------------------

        model = glm::mat4(1.0f);

        model = glm::translate(
            model,
            lightPos
        );

        model = glm::scale(
            model,
            glm::vec3(0.20f)
        );


        glUniformMatrix4fv(
            glGetUniformLocation(
                lampshader.Program,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );


        glBindVertexArray(VAO);

        glDrawArrays(
            GL_TRIANGLES,
            0,
            36
        );


        // ---------------------------------------------------------
        // LUNA
        // ---------------------------------------------------------

        model = glm::mat4(1.0f);

        model = glm::translate(
            model,
            lightPos2
        );

        model = glm::scale(
            model,
            glm::vec3(0.20f)
        );


        glUniformMatrix4fv(
            glGetUniformLocation(
                lampshader.Program,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );


        glDrawArrays(
            GL_TRIANGLES,
            0,
            36
        );


        glBindVertexArray(0);


        // Swap the buffers
        glfwSwapBuffers(window);
    }


    // ---------------------------------------------------------
    // DELETE
    // ---------------------------------------------------------

    glDeleteVertexArrays(
        1,
        &VAO
    );

    glDeleteBuffers(
        1,
        &VBO
    );


    glfwTerminate();

    return 0;
}


// ---------------------------------------------------------
// MOVEMENT
// ---------------------------------------------------------

void DoMovement()
{
    // Camera controls

    if (keys[GLFW_KEY_W] ||
        keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(
            FORWARD,
            deltaTime
        );
    }


    if (keys[GLFW_KEY_S] ||
        keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(
            BACKWARD,
            deltaTime
        );
    }


    if (keys[GLFW_KEY_A] ||
        keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(
            LEFT,
            deltaTime
        );
    }


    if (keys[GLFW_KEY_D] ||
        keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(
            RIGHT,
            deltaTime
        );
    }
}


// ---------------------------------------------------------
// KEY CALLBACK
// ---------------------------------------------------------

void KeyCallback(
    GLFWwindow* window,
    int key,
    int scancode,
    int action,
    int mode
)
{
    // Escape
    if (
        GLFW_KEY_ESCAPE == key &&
        GLFW_PRESS == action
        )
    {
        glfwSetWindowShouldClose(
            window,
            GL_TRUE
        );
    }


    // Guardar teclas
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }


    // ESPACIO = iniciar / detener animación

    if (
        key == GLFW_KEY_SPACE &&
        action == GLFW_PRESS
        )
    {
        activanim = !activanim;
    }
}


// ---------------------------------------------------------
// MOUSE CALLBACK
// ---------------------------------------------------------

void MouseCallback(
    GLFWwindow* window,
    double xPos,
    double yPos
)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;

        firstMouse = false;
    }


    GLfloat xOffset =
        xPos - lastX;

    GLfloat yOffset =
        lastY - yPos;


    lastX = xPos;
    lastY = yPos;


    camera.ProcessMouseMovement(
        xOffset,
        yOffset
    );
}