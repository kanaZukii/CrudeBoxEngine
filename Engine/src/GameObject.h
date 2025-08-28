#pragma once

#include <vector>
#include <type_traits>
#include <string>

#include "Math.h"
#include "components/Component.h"
#include "components/Transform.h"


class GameObject {
    public:
        Transform transform;

        GameObject(const char* name);

        ~GameObject();

        const std::vector<Component*>& componentList() const { return components;}

        Component* addComponent(Component* comp) {
            comp->owner = this;
            comp->generateID();
            components.push_back(comp);
            comp->init();
            return comp;
        }

        // Get a component of type T
        template<typename T>
        T* getComponent() {
            for (Component* c : components) {
                if (T* casted = dynamic_cast<T*>(c))
                    return casted;
            }
            return nullptr;
        }

        // Get all components of type T
        template<typename T>
        std::vector<T*> getComponents() {
            std::vector<T*> result;
            for (Component* c : components) {
                if (T* casted = dynamic_cast<T*>(c))
                    result.push_back(casted);
            }
            return result;
        }

    private:
        static int ID_Count;
        int UID = -1; 
        bool serialize = true;
        bool dead = false;

        std::vector<Component*> components;
        std::string name;

        void generateID();
};