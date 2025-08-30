#pragma once

#include <vector>

class Shader;
class Camera;
class GameObject;
class SpriteRenderer;
class RenderBatch;

class Renderer{
    public:
        Renderer(int batchSize){ if(batchSize < 10) batchSize = 500; batch_size = batchSize; }
        static void setCamera(Camera& camera) {sceneCamera = &camera;}
        static void bindShader(Shader& shader) { currentShader = &shader;}
        static Shader* getShader() { return currentShader; }
        void add(GameObject& gameObject);
        void render();
        void destroyGameObject(GameObject& gameObject);

    private:
        int batch_size = 1000;
        std::vector<RenderBatch*> batches;
        static Shader* currentShader;
        static Camera* sceneCamera;
        void addToBatch(SpriteRenderer& sprite);
};