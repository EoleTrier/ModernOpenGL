
#include "Ressources/Application.h"


Application app;

int main(int, char**)
{


    while (!glfwWindowShouldClose(app.window))
    {
        if (glfwGetKey(app.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            return 0;
        }
        app.Update();
        

        glfwSwapBuffers(app.window);
        glfwPollEvents();
    }

    app.~Application();

    glfwTerminate();
    return 0;
}
