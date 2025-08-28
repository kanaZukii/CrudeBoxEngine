#include "Engine.h"

#include <string>
#include <iostream>

#include "window/Window.h"
#include "window/InputListener.h"
#include "renderer/Shader.h"
#include "scene/Scene.h"
#include "renderer/Renderer.h"
#include <vector>

namespace CrudeBox {

    static Window* window = nullptr;
    static const char* title;
    static int width, height;

    static Shader* shader = nullptr;
    static Scene* scene = nullptr;
    static Renderer* renderer = nullptr;

    static Scene* getCurrentScene(){
        return scene;
    }

    void setWinTitle(const char* title){
        CrudeBox::title = title;
    }

    void setWinSize(int width, int height){
        CrudeBox::width = width; CrudeBox::height = height;
    }

    int getWinWidth(){
        return width;
    }

    int getWinHeight(){
        return height;
    }

    void init() {
        window = new Window(title, width, height);
        
        scene = new Scene();

        shader = new Shader("assets/default.glsl");
        shader->compile();

        renderer = new Renderer(1000);
        renderer->setCamera(scene->getCamera());
        renderer->bindShader(*shader);
    }

    bool isRunning(){
        return !window->windowHasClosed();
    }

    void update(float deltaTime) {
        // Example: move camera with arrow keys
        if(KeyListener::isKeyPressed(GLFW_KEY_UP))
            scene->getCamera().addPosition(Vector2(0.0f, 2.0f));
        if(KeyListener::isKeyPressed(GLFW_KEY_DOWN))
            scene->getCamera().addPosition(Vector2(0.0f, -2.0f));
        if(KeyListener::isKeyPressed(GLFW_KEY_LEFT))
            scene->getCamera().addPosition(Vector2(-2.0f, 0.0f));
        if(KeyListener::isKeyPressed(GLFW_KEY_RIGHT))
            scene->getCamera().addPosition(Vector2(2.0f, 0.0f));
    }

    void beginFrame(){
        window->beginFrame();
        shader->use();

        renderer->render();
    }
        
    void endFrame(){
        window->endframe();
    }

    void terminate() {
        shader->unuse();
        window->terminate();
    }

}