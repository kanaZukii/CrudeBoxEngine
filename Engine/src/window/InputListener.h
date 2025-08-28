#pragma once

#include <GLFW/glfw3.h>

#define MAX_MOUSEBUTTONS GLFW_MOUSE_BUTTON_LAST + 1
#define MAX_KEYS GLFW_KEY_LAST + 1

class MouseListener{
    public: 
        MouseListener();
        static MouseListener* get();
        static void mousePosCallback(GLFWwindow* window, double xPos, double yPos);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
        static void endFrame();
        static float getX();
        static float getY();
        static float getXScroll();
        static float getYScroll();
        static bool isDragging();
        static bool isButtonDown(int button);

    private:
        static MouseListener* instance;
        double xScroll, yScroll;
        double xPos, yPos, prevX, prevY;
        bool mouseButtonPressed[MAX_MOUSEBUTTONS] = {false};
        int mouseButtonDown;
        bool mouseDragging = false;
};

class KeyListener{
    public:
        KeyListener();
        static KeyListener* get();
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static bool isKeyPressed(int keyCode);
        static bool isKeyFirstPressed(int keyCode);

    private:
        static KeyListener* instance;
        bool keyPressed[MAX_KEYS] = {false};
        bool keyFirstPressed[MAX_KEYS] = {false};

};