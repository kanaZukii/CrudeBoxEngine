#pragma once

#include <string>

#include "Math.h"

class Shader{
    public:
        Shader(const char* glslFile);
        ~Shader();
        void compile();
        void use();
        void unuse();
        unsigned getID();
        void uploadMatrix4(const char* varname, const Matrix4& mat4);
        void uploadMatrix3(const char* varname, const Matrix3& mat3);
        void uploadVector4(const char* varname, const Vector4& vec4);
        void uploadVector3(const char* varname, const Vector3& vec3);
        void uploadVector2(const char* varname, const Vector2& vec2);
        void uploadIntArr(const char* varname, const int* arr, int count);
        void uploadFloat(const char* varname, float val);
        void uploadInt(const char* varname, int val);
        std::string vertexSrc, fragmentSrc;
    
    private:
        std::string filepath;
        unsigned int shaderID = 0;
        bool inUse = false;

        std::string loadFile(const std::string& filepath);
        void link(unsigned int vertex, unsigned int fragment);

};