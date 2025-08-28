#include "Window.h"

#include <iostream>
#include <Math.h>

#include "InputListener.h"

GLFWwindow* Window::glfwWindow = nullptr;

Window::Window(const char* title, int width, int height) {
    this->title = title;
    this->width = width;
    this->height = height;
    /* Initialize the library */
    if (!glfwInit())
        return;

    // Set required OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // required on macOS

    /* Create a windowed mode window and its OpenGL context */
    glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!glfwWindow)
    {
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(glfwWindow);

    glfwSwapInterval(1); // enable vsync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // For alpha blending and transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetWindowUserPointer(glfwWindow, this);

    /* Mouse Callbacks */
    glfwSetCursorPosCallback(glfwWindow, MouseListener::mousePosCallback);
    glfwSetMouseButtonCallback(glfwWindow, MouseListener::mouseButtonCallback);
    glfwSetScrollCallback(glfwWindow, MouseListener::mouseScrollCallback);

    /* Key Callbacks */
    glfwSetKeyCallback(glfwWindow, KeyListener::keyCallback);
    glfwSetFramebufferSizeCallback(glfwWindow, Window::windowSizeCallback);
}

void Window::windowSizeCallback(GLFWwindow* window, int newWidth, int newHeight){
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if(self){
        self->width = newWidth;
        self->height = newHeight;

        std::cout << "Width: " << self->width;
        std::cout << " Height: " << self->height << std::endl; 
    }
}

void Window::setWidth(int width){
    this->width = width;
}

void Window::setHeight(int height){
    this->height = height;
}

bool Window::windowHasClosed(){
    return glfwWindowShouldClose(glfwWindow);
}

void Window::beginFrame() {
    /* Render here */
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
}

void Window::endframe(){
    glfwPollEvents();
    /* Swap front and back buffers */
    glfwSwapBuffers(glfwWindow);
}

void Window::terminate() {
    glfwDestroyWindow(glfwWindow);
    glfwTerminate();
}
