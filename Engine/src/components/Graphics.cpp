#include "Graphics.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const char* filepath){
    this->filepath = filepath;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set Texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrap X
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrap Y

     // When stretching, pixelate the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* image = stbi_load(filepath, &width, &height, &channels, 0);

    if(image != nullptr){
        GLenum format;
        if (channels == 4) format = GL_RGBA;
        else if (channels == 3) format = GL_RGB;
        else if (channels == 1) format = GL_RED;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
        //glGenerateMipmap(GL_TEXTURE_2D); // optional, but good practice
    } else {
        std::cout << "Failed to load image: " << stbi_failure_reason() << std::endl;
    }

    stbi_image_free(image);
    glBindTexture(GL_TEXTURE_2D, 0); // unbind after loading
}

Texture::~Texture() {
    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
    }
}

void Texture::bind() const{
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbind() const{
    glBindTexture(GL_TEXTURE_2D, 0);
}


SpriteRenderer::SpriteRenderer(){
    setDirty();
}

void SpriteRenderer::setSprite(Sprite& sprite){
    this->sprite = &sprite;
    setDirty();
}

void SpriteRenderer::setColor(Vector4& color){
    this->colors = color;
}

void SpriteRenderer::setDirty(){
    dirty = true;
}

void SpriteRenderer::setClean(){
    dirty = false;
}

void SpriteRenderer::flipHorizontal(){
    for(Vector2& coord : getTexCoords()){
        coord.x = 1.0f - coord.x;
    }
    setDirty();
    flipped = !flipped;
}
    
void SpriteRenderer::flipVertical(){
    for(Vector2& coord : getTexCoords()){
        coord.y = 1.0f - coord.y;
    }
    setDirty();
    flipped = !flipped;
}