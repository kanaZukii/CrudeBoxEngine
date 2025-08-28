#pragma once

#include <array>
#include <string>

#include "Component.h"
#include "Math.h"

class Texture{
    public:
        Texture(const char* filepath);
        ~Texture();
        int getWidth() const { return width; }
        int getHeight() const { return height; }
        unsigned int getID() const { return textureID; }
        const std::string& getfilepath() const { return filepath; }
        void bind() const;
        void unbind() const;

        bool operator==(const Texture& b) const { return filepath == b.getfilepath(); }
        bool operator!=(const Texture& b) const { return !(*this == b); }

    private:
        std::string filepath;
        unsigned int textureID = 0;
        int width = 0, height = 0, channels = 0;
};

struct Sprite{
    Texture* texture = nullptr;
    std::array<Vector2, 4> texCoords = {
        Vector2(1.0f, 1.0f),
        Vector2(1.0f, 0.0f),
        Vector2(0.0f, 0.0f),
        Vector2(0.0f, 1.0f)
    };

    Sprite(){}
    Sprite(Texture& newTexture) : texture(&newTexture) {}
};

class SpriteRenderer : public Component{
    public:
        SpriteRenderer();
        void setSprite(Sprite& sprite);
        const Vector4 getColor() const { return colors; }
        std::array<Vector2, 4>& getTexCoords() { return sprite->texCoords; }
        Sprite* getSprite() const { return sprite; }
        Texture* getTexture() const { return sprite->texture; }
        void setDirty();
        void setClean();
        void flipHorizontal();
        void flipVertical();
        bool isDirty() {return dirty;}
        bool isFlipped() {return flipped;}

    private:
        Sprite* sprite = nullptr;
        Vector4 colors = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
        bool dirty = false;
        bool flipped = false;
};