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


unsigned int Application::VBO, Application::VAO;

Camera Application::camera(Vector3(0.0f, 0.0f, 3.0f));
float Application::lastX = 400, Application::lastY = 300;
float Application::yaw = 0, Application::pitch = 0;
bool Application::firstMouse = true;
Vector3 Application::cameraFront;

float Application::deltaTime;
float Application::lastFrame;

float Application::Width = 800;
float Application::Height = 600;

unsigned int Application::texture1, Application::texture2;
GLFWwindow* Application::window;


Shader Application::ourShader("Source/shaders/shader.vs", "Source/shaders/shader.fs");


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

    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Shader ourShader("Source/shaders/shader.vs", "Source/shaders/shader.fs");

    Model* viking = resourceManager.Create<Model>("model_viking");
    viking->shader = ourShader;
    viking->Load("Assets/meshes/viking_room.obj", "Assets/textures/viking_room.jpg");
    //resourceManager.Delete("model_viking");

    glEnable(GL_DEPTH_TEST);
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

   

    Model* vikingcopy = resourceManager.Get<Model>("model_viking");
    vikingcopy->Draw(camera);

}