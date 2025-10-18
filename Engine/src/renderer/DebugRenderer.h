#pragma once

#include <vector>

#include "Math.h"

class Shader;
class Camera;

struct Line2D{
    Vector2 start, end;
    Vector3 color;
    int duration;

    Line2D() : color(Vector3(1.0f, 1.0f, 1.0f)), duration(1) {}

    Line2D(Vector2 startPos, Vector2 endPos, Vector3 colors, int time) : 
                    start(startPos), 
                    end(endPos), 
                    color(colors),
                    duration(time) {}
    
    int beginFrame(){
        duration--;
        return duration;
    }
};

class DebugRenderer{
    public:
    static void init();
    static void bindShader(Shader &shader) { DebugRenderer::shader = &shader;}
    static void beginFrame();
    static void render(Camera &camera);
    static void addLine(Vector2 startPos, Vector2 endPos);
    static void addLine(Vector2 startPos, Vector2 endPos, Vector3 color);
    static void addLine(Vector2 startPos, Vector2 endPos, Vector3 color, int duration);
    static void addRect(Vector2 center, Vector2 dimension, float rotation);
    static void addRect(Vector2 center, Vector2 dimension, float rotation, Vector3 color);
    static void addRect(Vector2 center, Vector2 dimension, float rotation, Vector3 color, int duration);
    static void addCircle(Vector2 center, float radius);
    static void addCircle(Vector2 center, float radius, Vector3 color);
    static void addCircle(Vector2 center, float radius, Vector3 color, int duration);

    private:
    static unsigned int VAO, VBO;
    static bool started;
    static std::vector<float> vertexArr;

    static int MAX_LINES;
    static std::vector<Line2D> lines;
    static Shader* shader;
};