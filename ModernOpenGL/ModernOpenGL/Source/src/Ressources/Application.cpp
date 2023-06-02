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
#include "LowRenderer/Light/Directional.h"
#include "LowRenderer/Light/Point.h"
#include "LowRenderer/Light/Spot.h"

Camera Application::camera(Vector3(0.0f, 0.0f, 3.0f));
float Application::lastX = 400, Application::lastY = 300;
float Application::yaw = 0, Application::pitch = 0;
bool Application::firstMouse = true;
Vector3 Application::cameraFront;

float Application::deltaTime;
float Application::lastFrame;

float Application::Width = 800;
float Application::Height = 600;

unsigned int Application::cubeVBO, Application::cubeVAO;
unsigned int Application::lightCubeVAO;

Vector3 Application::cubePositions[] = {
        Vector3(0.0f,  0.0f,  0.0f),
        Vector3(2.0f,  5.0f, -15.0f),
        Vector3(-1.5f, -2.2f, -2.5f),
        Vector3(-3.8f, -2.0f, -12.3f),
        Vector3(2.4f, -0.4f, -3.5f),
        Vector3(-1.7f,  3.0f, -7.5f),
        Vector3(1.3f, -2.0f, -2.5f),
        Vector3(1.5f,  2.0f, -2.5f),
        Vector3(1.5f,  0.2f, -1.5f),
        Vector3(-1.3f,  1.0f, -1.5f)
};

Vector3 Application::pointLightPositions[] = {
        Vector3(0.7f,  0.2f,  2.0f),
        Vector3(2.3f, -3.3f, -4.0f),
        Vector3(-4.0f,  2.0f, -12.0f),
        Vector3(0.0f,  0.0f, -3.0f)
};


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
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };



    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Texture* text = resourceManager.Create<Texture>("viking_texture");
    text->Load("Assets/textures/viking_room.jpg");

    Shader* lightingShader = resourceManager.Create<Shader>("lighting");
    Shader* lightCubeShader = resourceManager.Create<Shader>("lightCube");

    lightingShader->SetVertexAndFragmentShader("Source/shaders/lighting.vs", "Source/shaders/lighting.fs");
    lightCubeShader->SetVertexAndFragmentShader("Source/shaders/lightCube.vs", "Source/shaders/lightCube.fs");

    lightingShader->use();
    lightingShader->setInt("material.diffuse", 0);
    lightingShader->setInt("material.specular", 1);
    /*
    Shader* shad = resourceManager.Create<Shader>("viking_shader");
    shad->SetVertexAndFragmentShader("Source/shaders/shader.vs", "Source/shaders/shader.fs");
    Texture* text2 = resourceManager.Create<Texture>("viking_texture");
    text2->Load("Assets/textures/viking_room.jpg");

    Model* viking = resourceManager.Create<Model>("model_viking");
    viking->Load("Assets/meshes/viking_room.obj", "Assets/textures/viking_room.jpg");

    Mesh mesh(viking, shad, text2);
    */
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
    {
        camera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
    }
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

    lighting->SetViewPos(camera.Position);
    lighting->setFloat("material.shininess", 32.0f);

    // directional light
    DirectionalLight dir1(Vector3(0.4f), Vector3(0.05f), Vector3(0.5f), 0); 
    dir1.SetDirectionalLight(lighting, Vector3(-0.2f, -1.0f, -0.3f));
    // point light 1
    PointLight point1(Vector3(0.8f), Vector3(0.05f), Vector3(1.0f), 0);
    point1.SetPointLight(lighting, pointLightPositions[0], 1.0f, 0.09f, 0.032f);
    // point light 2
    PointLight point2(Vector3(0.8f), Vector3(0.05f), Vector3(1.0f), 1);
    point2.SetPointLight(lighting, pointLightPositions[1], 1.0f, 0.09f, 0.032f);
    // point light 3
    PointLight point3(Vector3(0.8f), Vector3(0.05f), Vector3(1.0f), 2);
    point3.SetPointLight(lighting, pointLightPositions[2], 1.0f, 0.09f, 0.032f);
    // point light 4
    PointLight point4(Vector3(0.8f), Vector3(0.05f), Vector3(1.0f), 3);
    point4.SetPointLight(lighting, pointLightPositions[3], 1.0f, 0.09f, 0.032f);
    // spotLight
    SpotLight spot1(Vector3(1.0f), Vector3(0.0f), Vector3(1.0f), 0);
    spot1.SetSpotLight(lighting, camera.Position, camera.Front, 1.0f, 0.09f, 0.032f, 12.5f, 15.0f);


    Matrix4x4 projection = Matrix4x4::PerspectiveProjection(camera.Zoom * ToRadians, 800.f / 600.f, 0.1f, 1000.f);
    Matrix4x4 view = camera.GetViewMatrix();
    lighting->setMat4("projection", projection);
    lighting->setMat4("view", view);

    // world transformation
    Matrix4x4 model = Matrix4x4::identity();
    lighting->setMat4("model", model);

    Texture* diffuseMap = resourceManager.Get<Texture>("viking_texture");
    Texture* specularMap = resourceManager.Get<Texture>("viking_texture");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMap->ID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMap->ID);

    glBindVertexArray(cubeVAO);
    for (unsigned int i = 0; i < 10; i++)
    {
        Matrix4x4 model = Matrix4x4::identity();
        model = model * Matrix4x4::translate3D(cubePositions[i]);
        float angle = 20.0f * i;
        model = model * Matrix4x4::rotate(Vector3(ToRadians * angle, 0, 0));
        lighting->setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    lightCube->use();
    lightCube->setMat4("projection", projection);
    lightCube->setMat4("view", view);
   
    glBindVertexArray(lightCubeVAO);
    for (unsigned int i = 0; i < 4; i++)
    {
        Matrix4x4 model = Matrix4x4::TRS(Vector3(0), Vector3(pointLightPositions[i]), Vector3(0.2f));
        lightCube->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    //Model* vikingcopy = resourceManager.Get<Model>("model_viking");
    //vikingcopy->mesh.Draw(camera);

}