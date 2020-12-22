#include <glad/glad.h>
// Be sure to include GLAD before GLFW. The include file for GLAD includes the required OpenGL headers behind the scenes (like GL/gl.h) so be sure to include GLAD before other header files that require OpenGL (like GLFW). 
#include <GLFW/glfw3.h>
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);


int main() {
    glfwInit(); // Initialize GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // glfwWindowHint configures GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For MacOS

    // Create a window object
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL!", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initalize GLAD before we call an OpenGL function
    // glfwGetProcAddress defines the correct function based on which OS we're compiling for
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { 
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set dimensions via glViewport
    // 0,0 sets lower left corner of window, 800,600 are width and height of rendering window in pixels
    glViewport(0, 0, 800, 600);
    // We map from the range (-1 to 1) to (0, 800) and (0, 600)

    // We register the callback functions after we've created the window and before the render loop is initiated. 
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Simple render loop
    while (!glfwWindowShouldClose(window)) {
        // Input
        processInput(window);

        // Rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set clear color
        glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer

        // Check and call events and swap the buffers
        glfwSwapBuffers(window); // Swap color buffer (a large 2D buffer that contains color values for each pixel in GLFW's window)
        glfwPollEvents(); // Keyboard input or mouse movement events, updates window state, and calls corresponding functions (which we can register via callback methods)
    }

    // Properly clean/delete all of GLFW's resources that were allocated
    glfwTerminate();
    return 0;
}

// Deals with when the user resizes the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Process input
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}