#include "Engine.h"

#include <string>
#include <iostream>

#include "window/Window.h"
#include "renderer/Shader.h"
#include "scene/Scene.h"
#include "renderer/Renderer.h"

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

        shader = new Shader("assets/default.glsl");
        shader->compile();

        renderer = new Renderer(1000);
        renderer->bindShader(*shader);

        

        if(scene != nullptr){
            scene->initObjects();
        }
    }

    bool isRunning(){
        return !window->windowHasClosed();
    }

    void update(float deltaTime) {
        if(scene != nullptr){
            scene->update(deltaTime);
        }
    }

    void beginFrame(){
        window->beginFrame(); 
    }

    void render(){
        shader->use();
        if(scene != nullptr){
            scene->render();
        }
    }
        
    void endFrame(){
        window->endframe();
    }

    void terminate() {
        shader->unuse();
        window->terminate();
    }

}