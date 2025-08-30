#include "Scene.h"

#include <algorithm>

#include "renderer/Renderer.h"
#include "GameObject.h"

Scene::Scene(Renderer& renderer){
    this->renderer = &renderer;
    this->renderer->setCamera(camera);
}

void Scene::init(){

}

void Scene::initObjects(){
    for(GameObject* gameObj : sceneObjects) {
        gameObj->initComponents();
        renderer->add(*gameObj);
    }
    running = true;
}

void Scene::update(float deltaTime){
    camera.adjustProjection();
    for(GameObject* gameObj : sceneObjects) gameObj->update(deltaTime);
}

void Scene::render(){
    renderer->render();
}

void Scene::save(){

}

void Scene::load(){

}

void Scene::addGameObject(GameObject& gameObject){
    sceneObjects.push_back(&gameObject);
    if(running){
        gameObject.initComponents();
        renderer->add(gameObject);
    }
}

GameObject* Scene::getGameObjectbyUID(int UID){
    auto gameObj = std::find_if(sceneObjects.begin(), sceneObjects.end(),
    [UID](GameObject* obj) { return obj->getUID() == UID; });

    if (gameObj != sceneObjects.end()) return *gameObj;
    return nullptr;
}