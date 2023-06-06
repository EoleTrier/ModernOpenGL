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

Object* Application::world;

Camera Application::camera(Vector3(0.0f, 0.0f, 3.0f));
float Application::lastX = 400, Application::lastY = 300;
float Application::yaw = 0, Application::pitch = 0;
bool Application::firstMouse = true;
Vector3 Application::cameraFront;

float Application::deltaTime;
float Application::lastFrame;

float Application::Width = 800;
float Application::Height = 600;

GLFWwindow* Application::window;

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
        Log::Print("Failed to create GLFW window");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, Application::ResizeCallback);
    glfwSetCursorPosCallback(window, Application::MouseCallback);
    glfwSetScrollCallback(window, Application::ScrollCallback);

    gladLoadGL();
    glEnable(GL_DEPTH_TEST);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   
    Texture* text = resourceManager.Create<Texture>("viking_texture");
    text->Load("Assets/textures/viking_room.jpg");
    Shader* shad = resourceManager.Create<Shader>("viking_shader");
    shad->SetVertexAndFragmentShader("Source/shaders/lighting.vs", "Source/shaders/lighting.fs");

    Model* viking = resourceManager.Create<Model>("model_viking");
    viking->Load("Assets/meshes/viking_room.obj", "Assets/textures/viking_room.jpg");

    shad->Use();
    shad->SetInt("material.diffuse", 0);
    shad->SetInt("material.specular", 1);
    
    viking->mesh = new Mesh(viking, shad, text);
    Mesh* vikingMesh = viking->mesh;
    
    world = new Object();
    Object* v = new Object();
    v->mesh = vikingMesh;
    world->tranform.AddChild(&v->tranform);
   
    for (int i = 0; i < 10; i++)
    {
        Object* v1 = new Object();
        v1->mesh = vikingMesh;
        float x = rand() % 5;
        float y = rand() % 5;
        float z = rand() % 5;
        float a1 = rand() % 360;
        float a2 = rand() % 360;
        float a3 = rand() % 360;
        float s1 = rand() % 5;
        float s2 = rand() % 5;
        float s3 = rand() % 5;
        v1->tranform.position = Vector3(x, y, z);
        v1->tranform.rotation = Vector3(a1 * ToRadians, a2 * ToRadians, a3 * ToRadians);
        v1->tranform.scaling = Vector3(s1, s2, s3);

        v->tranform.AddChild(&v1->tranform);
    }
  
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
    float yoffset = lastY - ypos; 

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

void Draw(Object* obj, Camera& camera);
void Application::Update()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    ProcessInput(window, deltaTime);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    Shader* viking = resourceManager.Get<Shader>("viking_shader");
    viking->Use();
    viking->SetViewPos(camera.Position);
    viking->SetFloat("material.shininess", 8.0f);
    
    DirectionalLight dir1(Vector3(0.4f), Vector3(0.05f), Vector3(0.5f), Vector3(-0.2f, -1.0f, -0.3f), 0);
    dir1.SetDirectionalLight(viking);
    PointLight point1(Vector3(0.8f), Vector3(0.05f), Vector3(1.0f), Vector3(0, 0, 2), 1.0f, 0.09f, 0.032f, 0);
    point1.SetPointLight(viking);
    SpotLight spot1(Vector3(1.0f), Vector3(0.0f), Vector3(1.0f), camera.Position, camera.Front, 1.0f, 0.09f, 0.032f, 12.5f, 15.0f, 0);
    spot1.SetSpotLight(viking);
    

    Matrix4x4 projection = Matrix4x4::PerspectiveProjection(camera.Zoom * ToRadians, 800.f / 600.f, 0.1f, 1000.f);
    Matrix4x4 view = camera.GetViewMatrix();
    viking->SetMat4("projection", projection);
    viking->SetMat4("view", view);

    Matrix4x4 model = Matrix4x4::Identity();
    viking->SetMat4("model", model);

    Texture* diffuseMap = resourceManager.Get<Texture>("viking_texture");
    Texture* specularMap = resourceManager.Get<Texture>("viking_texture");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMap->id);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMap->id);
    
    world->tranform.rotation = world->tranform.rotation + Vector3(0.01f);
    world->tranform.UpdateSelfAndChilds();
    Draw(world, camera);
}

void Draw(Object* obj, Camera& camera)
{
    if (obj->mesh)
        obj->mesh->Draw(camera, obj->tranform.globalModel);

    for (Transform* const t : obj->tranform.childs)
    {
        Object* o = t->object;

        Draw(o, camera);
    }
}