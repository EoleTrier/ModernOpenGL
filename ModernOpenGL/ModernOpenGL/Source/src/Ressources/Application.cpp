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

Camera Application::mCamera(Vector3(0.0f, 0.0f, 3.0f));
float Application::mLastX = 400, Application::mLastY = 300;
float Application::mYaw = 0, Application::mPitch = 0;
bool Application::mFirstMouse = true;
Vector3 Application::mCameraFront;

float Application::mDeltaTime;
float Application::mLastFrame;

float Application::mWidth = 800;
float Application::mHeight = 600;

GLFWwindow* Application::window;

Application::Application()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   
    window = glfwCreateWindow(mWidth, mHeight, "ModernOpenGL", NULL, NULL);
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
   
    Texture* text = mResourceManager.Create<Texture>("viking_texture");
    text->Load("Assets/textures/viking_room.jpg");
    Shader* shad = mResourceManager.Create<Shader>("viking_shader");
    shad->SetVertexAndFragmentShader("Source/shaders/lighting.vs", "Source/shaders/lighting.fs");

    Model* viking = mResourceManager.Create<Model>("model_viking");
    viking->Load("Assets/meshes/viking_room.obj", "Assets/textures/viking_room.jpg");

    shad->Use();
    shad->SetInt("material.diffuse", 0);
    shad->SetInt("material.specular", 1);
    
    Mesh* mesh = mResourceManager.Create<Mesh>("viking_mesh");
    mesh->SetAttributesAndInit(viking, shad, text);
    viking->mesh = mesh;
    
    world = new Object();
    Object* v = new Object();
    v->mesh = mesh;
    world->tranform.AddChild(&v->tranform);
   
    for (int i = 0; i < 10; i++)
    {
        Object* v1 = new Object();
        v1->mesh = mesh;
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

    if (mFirstMouse)
    {
        mLastX = xpos;
        mLastY = ypos;
        mFirstMouse = false;
    }

    float xoffset = xpos - mLastX;
    float yoffset = mLastY - ypos; 

    mLastX = xpos;
    mLastY = ypos;

    mCamera.ProcessMouseMovement(xoffset, yoffset);
}

void Application::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    mCamera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void Application::ProcessInput(GLFWwindow* window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        mCamera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        mCamera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        mCamera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        mCamera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
    }
}

void Draw(Object* obj, Camera& Camera);
void Application::Update()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    mDeltaTime = currentFrame - mLastFrame;
    mLastFrame = currentFrame;

    ProcessInput(window, mDeltaTime);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    Shader* viking = mResourceManager.Get<Shader>("viking_shader");
    viking->Use();
    viking->SetViewPos(mCamera.Position);
    viking->SetFloat("material.shininess", 8.0f);
    
    DirectionalLight dir1(Vector3(0.4f), Vector3(0.05f), Vector3(0.5f), Vector3(-0.2f, -1.0f, -0.3f), 0);
    dir1.SetDirectionalLight(viking);
    PointLight point1(Vector3(0.8f), Vector3(0.05f), Vector3(1.0f), Vector3(0, 0, 2), 1.0f, 0.09f, 0.032f, 0);
    point1.SetPointLight(viking);
    SpotLight spot1(Vector3(1.0f), Vector3(0.0f), Vector3(1.0f), mCamera.Position, mCamera.Front, 1.0f, 0.09f, 0.032f, 12.5f, 15.0f, 0);
    spot1.SetSpotLight(viking);
    

    Matrix4x4 projection = Matrix4x4::PerspectiveProjection(mCamera.Zoom * ToRadians, 800.f / 600.f, 0.1f, 1000.f);
    Matrix4x4 view = mCamera.GetViewMatrix();
    viking->SetMat4("projection", projection);
    viking->SetMat4("view", view);

    Matrix4x4 model = Matrix4x4::Identity();
    viking->SetMat4("model", model);

    Texture* diffuseMap = mResourceManager.Get<Texture>("viking_texture");
    Texture* specularMap = mResourceManager.Get<Texture>("viking_texture");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMap->id);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMap->id);
    
    world->tranform.rotation = world->tranform.rotation + Vector3(0.01f);
    world->tranform.UpdateSelfAndChilds();
    Draw(world, mCamera);
}

void Draw(Object* obj, Camera& Camera)
{
    if (obj->mesh)
        obj->mesh->Draw(Camera, obj->tranform.globalModel);

    for (Transform* const t : obj->tranform.childs)
    {
        Object* o = t->object;

        Draw(o, Camera);
    }
}