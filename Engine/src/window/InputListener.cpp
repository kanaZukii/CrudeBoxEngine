#include "InputListener.h"

MouseListener* MouseListener::instance = nullptr;
MouseListener::MouseListener(){
    this->xPos =  0;
    this->yPos = 0;
    this->prevX = 0;
    this->prevY = 0;
    this->xScroll = 0;
    this->yScroll = 0;
}

MouseListener* MouseListener::get(){
    if(instance == nullptr){
        instance = new MouseListener();
    }

    return instance;
}

float MouseListener::getX(){
    return get()->xPos;
}

float MouseListener::getY(){
    return get()->yPos;
}


float MouseListener::getXScroll(){
    return get()->xScroll;
}


float MouseListener::getYScroll(){
    return get()->yScroll;
}

bool MouseListener::isDragging(){
    return get()->mouseDragging;
}


bool MouseListener::isButtonDown(int button){
    if(button < MAX_MOUSEBUTTONS){
        return get()->mouseButtonPressed[button];
    } else {
        return false;
    }
}

void MouseListener::mousePosCallback(GLFWwindow* window, double xPos, double yPos){
    if(get()->mouseButtonDown > 0){
        get()->mouseDragging = true;
    }
    get()->prevX = get()->xPos;
    get()->prevY = get()->yPos;

    get()->xPos = xPos;
    get()->yPos = yPos;
}

void MouseListener::mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset){
    get()->xScroll = xOffset;
    get()->yScroll = yOffset;
}

void MouseListener::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
    if(action == GLFW_PRESS){
        get()->mouseButtonDown++;
        if(button < sizeof(get()->mouseButtonPressed)/sizeof(get()->mouseButtonPressed[0])){
            get()->mouseButtonPressed[button] = true;
        }
    } else if(action == GLFW_RELEASE){
        get()->mouseButtonDown--;
        if(button < MAX_MOUSEBUTTONS){
            get()->mouseButtonPressed[button] = false;
            get()->mouseDragging = false;
        }
    }
}

KeyListener* KeyListener::instance = nullptr;
KeyListener::KeyListener(){}

KeyListener* KeyListener::get(){
    if(instance == nullptr){
        instance = new KeyListener;
    }

    return instance;
}

void KeyListener::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(action == GLFW_PRESS){
        if(key < MAX_KEYS){
            get()->keyPressed[key] = true;
            get()->keyFirstPressed[key] = true;
        }
    } else if(action == GLFW_RELEASE){
        if(key < MAX_KEYS){
            get()->keyPressed[key] = false;
            get()->keyFirstPressed[key] = false;
        }
    }
}

bool KeyListener::isKeyPressed(int keyCode){
    return get()->keyPressed[keyCode];
}

bool KeyListener::isKeyFirstPressed(int keyCode){
    bool res = get()->keyFirstPressed[keyCode];
    if(res){
        get()->keyFirstPressed[keyCode] = false;
    }

    return res;
}

