#pragma once

#include <array>
#include <vector>
#include <string>
#include <cstdint>

#include "Math.h"

class SpriteRenderer;
class Texture;
class Renderer;
class Camera;

#define POS_SIZE 2
#define COLOR_SIZE 4
#define TEX_COORDS_SIZE 2
#define TEX_ID_SIZE 1

#define POS_OFFSET 0
#define COLOR_OFFSET (POS_OFFSET + POS_SIZE * sizeof(float))
#define TEX_COORDS_OFFSET (COLOR_OFFSET + COLOR_SIZE * sizeof(float))
#define TEX_ID_OFFSET (TEX_COORDS_OFFSET + TEX_COORDS_SIZE * sizeof(float))

#define VERTEX_SIZE 10
#define VERTEX_SIZE_BYTES (VERTEX_SIZE * sizeof(float))


class RenderBatch {
    public:
        RenderBatch(int maxBatchSize, int zIndex, Renderer* renderer);
        void init();
        void render(Camera& camera);
        void terminate();
        const int getZ() const;
        const bool hasRoom() const;
        const bool hasRoomForTexture() const;
        const bool hasTexture(Texture& tex) const;
        void addSprite(SpriteRenderer& sprite);
        bool destroyIfExist();

    private:
        Renderer* renderer;
        unsigned int VBO = 0, VAO = 0, EBO = 0, maxBatchSize = 0;
        int zIndex = 0;

        const unsigned int texSize = 8;       
        std::array<int, 8> texSlots = {0,1,2,3,4,5,6,7};

        std::vector<SpriteRenderer*> sprites; 
        std::vector<Texture*> textures; 
        std::vector<float> vertices; 

        std::vector<uint32_t> generateIndices();
        static constexpr std::array<std::array<float,2>,4> quadSteps {{
            {1.0f, 1.0f},
            {1.0f, 0.0f},
            {0.0f, 0.0f},
            {0.0f, 1.0f}
            // Centered
            // { 0.5f,  0.5f},
            // { 0.5f, -0.5f},
            // {-0.5f, -0.5f},
            // {-0.5f,  0.5f}
        }};
        void loadElementIndices(std::vector<uint32_t>& elements, int index);
        void loadVertexProperties(int index);
};