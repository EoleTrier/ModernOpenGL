#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "LowRenderer/Camera.h"
#include "Core/Debug/Log.h"
#include "Core/Maths/Matrix4x4.h"
#include "Ressources/Shader.h"
#include "Ressources/ResourceManager.h"
#include "Core/Object.h"

class Application
{
public:
	static Object* world;
	static GLFWwindow* window;
	Application();
	~Application();
	void Update();

private:
	ResourceManager mResourceManager;
	static Camera mCamera;
	static float mLastX, mLastY;
	static float mYaw, mPitch;
	static bool mFirstMouse;
	static Vector3 mCameraFront;
	static float mDeltaTime;
	static float mLastFrame;
	static float mWidth, mHeight;

	static void ResizeCallback(GLFWwindow* window, int width, int height);
	static void MouseCallback(GLFWwindow* window, double xposIn, double yposIn);
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void ProcessInput(GLFWwindow* window, float deltaTime);

};