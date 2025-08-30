#pragma 

#include <vector>

#include "renderer/Camera.h"

class GameObject;
class Renderer;
class Shader;

class Scene {
    public:
        Scene(Renderer& renderer);
        virtual void init();
        virtual void initObjects();
        virtual void update(float deltaTime);
        virtual void render();
        virtual void save();
        virtual void load();

        Camera& getCamera() {return camera;}
        Renderer* getRenderer() {return renderer;}
        
        std::vector<GameObject*> getSceneObjects(){return sceneObjects;}
        void addGameObject(GameObject& gameObject);
        GameObject* getGameObjectbyUID(int UID);

    protected:
        std::vector<GameObject*> sceneObjects;
        Renderer* renderer = nullptr;
        Camera camera;
        bool running = false;

};