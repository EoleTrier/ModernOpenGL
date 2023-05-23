
#include "Ressources/Application.h"


Application app;

int main(int, char**)
{


    while (!glfwWindowShouldClose(app.window))
    {
        app.Update();

        glfwSwapBuffers(app.window);
        glfwPollEvents();
    }

    app.~Application();

    glfwTerminate();
    return 0;
}
