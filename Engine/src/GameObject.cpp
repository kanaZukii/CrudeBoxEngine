#include "GameObject.h"

int GameObject::ID_Count;

GameObject::GameObject(const char* name){
    this->name.assign(name);
    transform.scale = Vector2(32.0f, 32.0f);
}

GameObject::~GameObject() {
    for (Component* c : components) delete c;
}

void GameObject::generateID(){
    if(UID < 0){
        UID = ID_Count;
        ID_Count++;
    }
}

void GameObject::initComponents(){
    for( Component* comp : components) comp->init();
}

void GameObject::update(float deltaTime){
    for( Component* comp : components) comp->update(deltaTime);
}