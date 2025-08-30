#include "Renderer.h"

#include <algorithm>

#include "GameObject.h"
#include "renderer/Camera.h"
#include "renderer/Shader.h"
#include "components/Graphics.h"
#include "RenderBatch.h"

Shader* Renderer::currentShader = nullptr;
Camera* Renderer::sceneCamera = nullptr;

void Renderer::render(){
    currentShader->use();
    for(RenderBatch* rbatch : batches){
        rbatch->render(*sceneCamera);
    }
}

void Renderer::add(GameObject& gameObject){
    SpriteRenderer* spriteRender = gameObject.getComponent<SpriteRenderer>();
    if(spriteRender != nullptr) addToBatch(*spriteRender);
}

void Renderer::addToBatch(SpriteRenderer& sprite){
    bool added = false;
    for(RenderBatch* rbatch : batches){
        if(rbatch->hasRoom() && rbatch->getZ() == sprite.getOwner()->transform.zIndex){
            Texture* tex = sprite.getTexture();
            if(tex == nullptr || rbatch->hasTexture(*tex) || rbatch->hasRoomForTexture()){
                rbatch->addSprite(sprite);
                added = true;
                break;
            }
        }
    }

    if(!added){
        RenderBatch* batch = new RenderBatch(batch_size, sprite.getOwner()->transform.zIndex, this);
        batch->init();
        batch->addSprite(sprite);
        batches.push_back(batch);
        
        std::sort(batches.begin(), batches.end(),
            [](auto& a, auto& b){ return a->getZ() < b->getZ(); });
    }
}
