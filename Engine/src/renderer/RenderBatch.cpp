#include "RenderBatch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "GameObject.h"
#include "Renderer.h"
#include "Shader.h"
#include "Camera.h"
#include "components/Graphics.h"

RenderBatch::RenderBatch(int maxBatchSize, int zIndex, Renderer* renderer){
    this->maxBatchSize = maxBatchSize;
    this->zIndex = zIndex;
    this->renderer = renderer;

    vertices.resize(maxBatchSize * 4 * VERTEX_SIZE);
    sprites.reserve(maxBatchSize);
    textures.reserve(texSize);

    std::cout << "Created a batch" << std::endl;
}

void RenderBatch::init(){
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
    
    std::vector<uint32_t> indices = generateIndices();
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

    // layout(location = 0) → vec3 position
    glVertexAttribPointer(0, POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, (void*)POS_OFFSET);
    glEnableVertexAttribArray(0);

    // layout(location = 1) → vec4 color
    glVertexAttribPointer(1, COLOR_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, (void*)COLOR_OFFSET);
    glEnableVertexAttribArray(1);

    // layout(location = 2) → vec2 texCoords
    glVertexAttribPointer(2, TEX_COORDS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, (void*)TEX_COORDS_OFFSET);
    glEnableVertexAttribArray(2);

    // layout(location = 3) → float texID
    glVertexAttribPointer(3, TEX_ID_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, (void*)TEX_ID_OFFSET);
    glEnableVertexAttribArray(3);
}

std::vector<uint32_t> RenderBatch::generateIndices(){
    // 6 per quad (3 per triangle)
    std::vector<uint32_t> elements;
    elements.reserve(6 * maxBatchSize);

    for(int i = 0; i < maxBatchSize; i++){
        loadElementIndices(elements, i);
    }

    return elements;
}

void RenderBatch::loadElementIndices(std::vector<uint32_t>& elements, int index){
    // Each quad has 4 vertices
    int offset = 4 * index;

    // 3, 2, 0, 0, 2, 1     7, 6, 4, 4, 6, 5
    // Triangle 1
    elements.push_back(offset + 3);
    elements.push_back(offset + 2);
    elements.push_back(offset);

    //Triangle 2
    elements.push_back(offset);
    elements.push_back(offset + 2);
    elements.push_back(offset + 1);
}

void RenderBatch::loadVertexProperties(int index){
    SpriteRenderer* sprite =  sprites[index];
    // Find the offset wihin array (4 vertices per sprite)
    int offset = index * 4 * VERTEX_SIZE;

    Vector4 color = sprite->getColor();
    std::array<Vector2, 4> texCoords = sprite->getTexCoords();

    int texID = 0;
    bool found = false;
    if(sprite->getTexture() != nullptr){
        for(int i = 0; i < textures.size(); i++){
            if(textures[i]->getfilepath() == sprite->getTexture()->getfilepath()){
                texID = i + 1;
                found = true;
                break;
            }
        }
        if(!found){
            std::cerr << "Sprite Texture: '" << sprite->getTexture()->getfilepath() <<  "' Exist but not found";
        }
    }

    Matrix4 transformMatrix = Matrix4::identity();
    // TODO: Implement Rotation

    // Add vertices with the properties
    for(int i = 0; i < 4; i++){
        float xStep = quadSteps[i][0];
        float yStep = quadSteps[i][1];

        // Load position
        float posX = sprite->getOwner()->transform.position.x;
        float posY = sprite->getOwner()->transform.position.y;
        float scaleX = sprite->getOwner()->transform.scale.x;
        float scaleY = sprite->getOwner()->transform.scale.y;

        Vector4 currentPosition = Vector4(posX + (xStep * scaleX),  posY + (yStep * scaleY), 0, 1);
        
        // Load position
        vertices[offset] = currentPosition.x;
        vertices[offset+1] = currentPosition.y;

        // Load Color
        vertices[offset+2] = color.x;
        vertices[offset+3] = color.y;
        vertices[offset+4] = color.z;
        vertices[offset+5] = color.w;

        // Load texture Coordinates
        vertices[offset+6] = texCoords[i].x;
        vertices[offset+7] = texCoords[i].y;

        //Load texture ID
        vertices[offset+8] = texID;

        offset += VERTEX_SIZE;
    }
}

void RenderBatch::addSprite(SpriteRenderer& sprite){
    if(sprites.size() >= maxBatchSize) return;

    sprites.push_back(&sprite);
    if(sprite.getTexture() != nullptr){
        if(!hasTexture(*sprite.getTexture())){
            textures.push_back(sprite.getTexture());
        }
    }

    loadVertexProperties(sprites.size() - 1);
}


// bool RenderBatch::destroyIfExist(){

// }

void RenderBatch::render(Camera& camera){

    bool rebufferData = false;
     // Loop through sprites if something has changed
    for(int i = 0; i < sprites.size(); i++){
        SpriteRenderer* sprite = sprites[i];
        if(sprite->isDirty()){
            loadVertexProperties(i);
            sprite->setClean();
            rebufferData = true;
        }

        // TODO: Add delete if exist
    }

    if(rebufferData){
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
    }

    Shader* shader = renderer->getShader();
    shader->uploadMatrix4("uProjection", camera.getProjection());
    shader->uploadMatrix4("uView", camera.getView());

    for(int i = 0; i < textures.size(); i++){
        glActiveTexture(GL_TEXTURE0 + i + 1);
        textures[i]->bind();
    }
    shader->uploadIntArr("uTextures", texSlots.data(), texSlots.size());

    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawElements(GL_TRIANGLES, sprites.size() * 6, GL_UNSIGNED_INT, 0);

     // Unbinding current attributes for the next draw call
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
    
    for(int i = 0; i < textures.size(); i++){
            textures[i]->unbind();
        }

    shader->unuse();
}

void RenderBatch::terminate(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

const int RenderBatch::getZ() const{
    return zIndex;
}

const bool RenderBatch::hasRoom() const{
    return sprites.size() < maxBatchSize;
}

const bool RenderBatch::hasRoomForTexture() const{
    return textures.size() < texSize;
}


const bool RenderBatch::hasTexture(Texture& tex) const{
    return std::any_of(textures.begin(), textures.end(),
                       [&](Texture* t) { return *t == tex; });
}
