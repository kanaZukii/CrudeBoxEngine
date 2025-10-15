#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "DebugRenderer.h"
#include "components/Graphics.h"
#include "Shader.h"
#include "Camera.h"

int DebugRenderer::MAX_LINES = 500;
bool DebugRenderer::started = false;
Shader* DebugRenderer::shader = nullptr;

void DebugRenderer::init(){
    lines.reserve(MAX_LINES);
    vertexArr.resize(MAX_LINES * 6 * 2);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexArr.size() * sizeof(float), vertexArr.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glLineWidth(2.0f);
}

void DebugRenderer::beginFrame(){
    if(!started){
        init();
        started = true;
    }

    for (int i = 0; i < static_cast<int>(lines.size()); i++) {
        if (lines[i].beginFrame() < 0) {
            lines.erase(lines.begin() + i);
            i--;
        }
    }
}

void DebugRenderer::render(Camera &camera){
    if(lines.size() <= 0) return;
    
    int index = 0;

    for(Line2D line : lines){
        for(int i = 0; i < 2; i++){
            Vector2 position = i == 0 ? line.start : line.end;
            Vector3 color = line.color;

            // Load Position
            vertexArr[index] = position.x;
            vertexArr[index + 1] = position.y;
            vertexArr[index + 2] = -10.0f;

            // Load the color
            vertexArr[index + 3] = color.x;
            vertexArr[index + 4] = color.y;
            vertexArr[index + 5] = color.z;

            index += 6;
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    int lineVertexCount = lines.size() * 2;
    glBufferSubData(GL_ARRAY_BUFFER, 0, lineVertexCount * 6 * sizeof(float), vertexArr.data());

    shader->use();
    shader->uploadMatrix4("uProjection", camera.getProjection());
    shader->uploadMatrix4("uView", camera.getView());

    // Bind VAO
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Draw the batch
    glDrawArrays(GL_LINES, 0, lineVertexCount);

    // Disable Location
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);

    shader->unuse();
}

void DebugRenderer::addLine(Vector2 startPos, Vector2 endPos, Vector3 colors, int duration){
    if(lines.size() >= MAX_LINES) return;

    Line2D line; 
    line.start = startPos; line.end = endPos;
    line.color = colors;
    line.duration = duration;

    lines.push_back(line);
}

void DebugRenderer::addRect(Vector2 center, Vector2 dimension, float rotation, Vector3 color, int duration){
    Vector2 min = center - (dimension / 2);
    Vector2 max = center + (dimension / 2);

    Vector2 vertices[] = {
        Vector2(min.x, min.y),  Vector2(min.x, max.y),
        Vector2(max.x, max.y),  Vector2(max.x, min.y)
    };

    if(rotation != 0.0f){
        for(Vector2& vect : vertices){
            rotateVec2(vect, rotation, center);
        }
    }

    addLine(vertices[0], vertices[1], color, duration);
    addLine(vertices[1], vertices[2], color, duration);
    addLine(vertices[2], vertices[3], color, duration);
    addLine(vertices[3], vertices[0], color, duration);
}

void DebugRenderer::addCircle(Vector2 center, float radius, Vector3 color, int duration){
    std::vector<Vector2> points;
    points.resize(24);
    float increment = 360/ points.size();
    float currentAngle = 0;

    for(int i = 0; i < points.size(); i++){
        Vector2 temp(radius, 0);
        rotateVec2(temp, currentAngle, Vector2());
        points[i] = temp + center;
        if(i > 0){
            addLine(points[i-1], points[i], color, duration);
        }
        currentAngle += increment;
    }

    addLine(points[points.size()-1], points[0], color, duration);
}

void DebugRenderer::addLine(Vector2 startPos, Vector2 endPos, Vector3 color){
    addLine(startPos, endPos, color, 1);
}

void DebugRenderer::addLine(Vector2 startPos, Vector2 endPos){
    Vector3 color(1.0f, 0.0f, 0.0f);
    addLine(startPos, endPos, color, 1);
}

void DebugRenderer::addRect(Vector2 center, Vector2 dimension, float rotation, Vector3 color){
    addRect(center, dimension, rotation, color, 1);
}

void DebugRenderer::addRect(Vector2 center, Vector2 dimension, float rotation){
    Vector3 color(1.0f, 0.0f, 0.0f);
    addRect(center, dimension, rotation, color, 1);
}

void DebugRenderer::addCircle(Vector2 center, float radius, Vector3 color){
    addCircle(center, radius, color, 1);
}

void DebugRenderer::addCircle(Vector2 center, float radius){
    Vector3 color(1.0f, 0.0f, 0.0f);
    addCircle(center, radius, color, 1);
}