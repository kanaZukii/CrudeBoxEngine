#include "Engine.h"

#include <string>
#include <iostream>

#include "window/Window.h"
#include "renderer/Shader.h"
#include "scene/Scene.h"
#include "renderer/Renderer.h"
#include "renderer/DebugRenderer.h"

namespace CrudeBox {

    static Window* window = nullptr;
    static const char* title;
    static int width, height;

    static bool debug = false;

    static Shader* gameShader = nullptr;
    static Shader* debugShader = nullptr;

    static Renderer* renderer = nullptr;
    static DebugRenderer* debugRenderer = nullptr;

    static Scene* scene = nullptr;

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

        gameShader = new Shader("assets/default.glsl");
        gameShader->compile();

        debugShader = new Shader("assets/debug.glsl");
        debugShader->compile();

        renderer = new Renderer(1000);

        debugRenderer = new DebugRenderer();
        debugRenderer->bindShader(*debugShader);

        if(scene != nullptr){
            scene->initObjects();
        }
    }

    bool isRunning(){
        return !window->windowHasClosed();
    }

    void setDebug(bool value){
        debug = value;
    }

    void update(float deltaTime) {
        if(scene != nullptr){
            scene->update(deltaTime);
        }
    }

    void beginFrame(){
        window->beginFrame(); 
        if(debug) {
            debugRenderer->beginFrame();
        }
    }

    void render(){

        if(debug) debugRenderer->render(scene->getCamera());

        renderer->bindShader(*gameShader);
        if(scene != nullptr){
            scene->render();
        }
    }
        
    void endFrame(){
        window->endframe();
    }

    void terminate() {
        gameShader->unuse();
        window->terminate();
    }

}