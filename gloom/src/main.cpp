// Local headers
#include "gloom/gloom.hpp"
#include "program.hpp"

// System headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


// A callback which allows GLFW to report errors whenever they occur
static void glfwErrorCallback(int error, const char *description)
{
  std::cerr << "GLFW returned an error:" << description << ", " << error << std::endl;
}


GLFWwindow* init_window()
{
    if (!glfwInit())
    {
    std::cerr << "Could not start GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Set core window options (adjust version numbers if needed)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Enable the GLFW runtime error callback function defined previously.
    glfwSetErrorCallback(glfwErrorCallback);

    // Set additional window options
    glfwWindowHint(GLFW_RESIZABLE, windowResizable);
    glfwWindowHint(GLFW_SAMPLES, windowSamples);  // MSAA

    // Create window using GLFW
    GLFWwindow* window = glfwCreateWindow(windowWidth,
                                          windowHeight,
                                          windowTitle.c_str(),
                                          nullptr,
                                          nullptr);

    // Ensure the window is set up correctly
    if (!window)
    {
        std::cerr << "Could not open GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Let the window be the current OpenGL context and initialise glad
    glfwMakeContextCurrent(window);
    gladLoadGL();

    // Print various OpenGL information to stdout
    printf("%s: %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
    printf("GLFW\t %s\n", glfwGetVersionString());
    printf("OpenGL\t %s\n", glGetString(GL_VERSION));
    printf("GLSL\t %s\n\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    return window;
}


int main(int argc, char* argb[])
{
    // Initialise window using GLFW
    GLFWwindow* window = init_window();

    // Run an OpenGL application using this window
    runProgram(window);

    // Terminate GLFW (no need to call glfwDestroyWindow)
    glfwTerminate();

    return EXIT_SUCCESS;
}
