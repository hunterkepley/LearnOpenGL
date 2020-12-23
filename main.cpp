#include <glad/glad.h>
// Be sure to include GLAD before GLFW. The include file for GLAD includes the required OpenGL headers behind the scenes (like GL/gl.h) so be sure to include GLAD before other header files that require OpenGL (like GLFW). 
#include <GLFW/glfw3.h>
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

// Vertex shader source
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// Fragment shader source
const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";


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

    // Making a triangle:

    // Triangle vertices
    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    // Generate buffer (VBO)
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // Bind GL_ARRAY_BUFFER to the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copy vertex data into the buffer's memory
    // (Type of buffer we want to copy data into, size of data, actual data, how we want the GPU to manage the given data)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // We've now stored the triangle's vertex data on the GPU (managed by VBO)

    // Vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Attach shader source to shader object and compile shader
    // (Shader object to compile, how many strings we're passing as source, actual source, NULL)
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check errors!
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check errors!
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Create shader program object
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // Attach previously compiled shaders then link them with glLinkProgram
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    }

    // Attach program
    glUseProgram(shaderProgram);
    // Every shader and rendering call will now use this program object (and thus the shaders)
    // Delete shader objects after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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