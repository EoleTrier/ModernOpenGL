#include <iostream>
#include "Ressources/Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Image/stb_image.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "Ressources/Application.h"
#include "Ressources/Model.h"
#include "Core/Debug/Assertion.h"
#include "Core/Debug/Log.h"
#include "LowRenderer/Mesh.h"


Camera Application::camera(Vector3(0.0f, 0.0f, 3.0f));
float Application::lastX = 400, Application::lastY = 300;
float Application::yaw = 0, Application::pitch = 0;
bool Application::firstMouse = true;
Vector3 Application::cameraFront;

ResourceManager Application::resourceManager;

float Application::deltaTime;
float Application::lastFrame;

float Application::Width = 800;
float Application::Height = 600;

unsigned int Application::cubeVBO, Application::cubeVAO;
unsigned int Application::lightCubeVAO;



GLFWwindow* Application::window;

Vector3 Application::lightPos(1.2f, 1.0f, 2.0f);

Application::Application()
{
    Width = 800;
    Height = 600;
    lastX = Width / 2;
    lastY = Height / 2;
    yaw = 0;
    pitch = 0;
    firstMouse = true;

    deltaTime = 0;
    lastFrame = 0;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(Width, Height, "ModernOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, Application::ResizeCallback);
    glfwSetCursorPosCallback(window, Application::MouseCallback);
    glfwSetScrollCallback(window, Application::ScrollCallback);

    gladLoadGL();
    glEnable(GL_DEPTH_TEST);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // second, configure the light's VAO (cubeVBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Shader* lightingShader = resourceManager.Create<Shader>("lighting");
    Shader* lightCubeShader = resourceManager.Create<Shader>("lightCube");

    lightingShader->SetVertexAndFragmentShader("Source/shaders/lighting.vs", "Source/shaders/lighting.fs");
    lightCubeShader->SetVertexAndFragmentShader("Source/shaders/lightCube.vs", "Source/shaders/lightCube.fs");

    /*Shader* shad = resourceManager.Create<Shader>("viking_shader");
    shad->SetVertexAndFragmentShader("Source/shaders/shader.vs", "Source/shaders/shader.fs");
    Texture* text = resourceManager.Create<Texture>("viking_texture");
    text->Load("Assets/textures/viking_room.jpg");

    Model* viking = resourceManager.Create<Model>("model_viking");
    viking->Load("Assets/meshes/viking_room.obj", "Assets/textures/viking_room.jpg");

    Mesh mesh(viking, shad, text);*/

    float deltaTime = 0;
    float lastFrame = 0;

}

Application::~Application()
{
   
}

void Application::ResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void Application::MouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void Application::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void Application::ProcessInput(GLFWwindow* window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
}

void Application::Update()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // input
    // -----
    ProcessInput(window, deltaTime);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    Shader* lighting = resourceManager.Get<Shader>("lighting");
    Shader* lightCube = resourceManager.Get<Shader>("lightCube");
    // be sure to activate shader when setting uniforms/drawing objects
    lighting->use();
    lighting->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    lighting->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    lighting->setVec3("lightPos", lightPos);
    lighting->setVec3("viewPos", camera.Position);

    // view/projection transformations
    Matrix4x4 projection = Matrix4x4::PerspectiveProjection(camera.Zoom * ToRadians, 800.f / 600.f, 0.1f, 1000.f);
    Matrix4x4 view = camera.GetViewMatrix();
    lighting->setMat4("projection", projection);
    lighting->setMat4("view", view);

    // world transformation
    Matrix4x4 model = Matrix4x4::identity();
    lighting->setMat4("model", model);


    // render the cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    // also draw the lamp object
    lightCube->use();
    lightCube->setMat4("projection", projection);
    lightCube->setMat4("view", view);
    model = Matrix4x4::identity();
    model = model.translate3D(lightPos);
    model = model.scaling3D(Vector3(0.2f)); // a smaller cube
    lightCube->setMat4("model", model);

    glBindVertexArray(lightCubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //Model* vikingcopy = resourceManager.Get<Model>("model_viking");
    //vikingcopy->mesh.Draw(camera);


}