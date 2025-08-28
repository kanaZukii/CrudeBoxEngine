#include "Math.h"

struct Transform {
    Vector2 position, scale;
    int zIndex = 0;

    Transform(){}
    Transform(Vector2 pos, Vector2 size) : position(pos), scale(size) {}
};