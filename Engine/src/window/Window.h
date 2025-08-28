#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window{
    public:
        static GLFWwindow* glfwWindow;
        Window(const char* title, int width, int height);
        void setWidth(int width);
        void setHeight(int height);
        void beginFrame();
        void endframe();
        void terminate();
        bool windowHasClosed();

    private:
        int width, height;
        const char* title;
        static void windowSizeCallback(GLFWwindow* window, int newWidth, int newHeight);
};