#pragma once
#include "renderer/Camera.h"

class Scene {
    public:
        Scene();
        void update(float deltaTime);
        Camera& getCamera();

    private:
        Camera camera;
};