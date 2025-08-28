#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream> 
#include <fstream>
#include <sstream>
#include <regex>

Shader::Shader(const char* glslFile) {
    filepath = glslFile;
    try {
        std::string source = loadFile(filepath);

        // Match "#type vertex" or "#type fragment"
        std::regex pattern(R"(#type\s+(vertex|fragment))");
        std::sregex_iterator iter(source.begin(), source.end(), pattern);
        std::sregex_iterator end;

        size_t lastPos = 0;
        std::string shaderType;

        for (; iter != end; ++iter) {
            shaderType = (*iter)[1].str(); // "vertex" or "fragment"
            size_t matchPos = iter->position();
            
            // The actual GLSL code starts after the matched line
            size_t lineEnd = source.find('\n', matchPos);
            if (lineEnd == std::string::npos) {
                throw std::runtime_error("Malformed shader file.");
            }

            std::string code = source.substr(lineEnd + 1, source.size() - lineEnd - 1);

            // If there’s another match ahead, cut before it
            auto nextIter = iter;
            ++nextIter;
            if (nextIter != end) {
                code = source.substr(lineEnd + 1, nextIter->position() - (lineEnd + 1));
            }

            if (shaderType == "vertex") {
                vertexSrc = code;
            } else if (shaderType == "fragment") {
                fragmentSrc = code;
            } else {
                throw std::runtime_error("Unknown shader type: " + shaderType);
            }
        }

        if (vertexSrc.empty() || fragmentSrc.empty()) {
            throw std::runtime_error("Shader file missing vertex or fragment section.");
        }

    } catch (const std::exception& e) {
        std::cerr << "Error loading shader: " << e.what() << std::endl;
    }
}

std::string Shader::loadFile(const std::string& filepath){
    std::ifstream file(filepath);
    if(!file.is_open()){
        throw std::runtime_error("Failed to open glsl file: " + filepath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Shader::compile(){
    unsigned int vertexID, fragmentID;

    vertexID = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexSourceStr = vertexSrc.c_str();

    glShaderSource(vertexID, 1, &vertexSourceStr, NULL);
    glCompileShader(vertexID);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << filepath << std::endl << infoLog << std::endl;
    }

    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSourceStr = fragmentSrc.c_str();
    glShaderSource(fragmentID, 1, &fragmentSourceStr, NULL);
    glCompileShader(fragmentID);

    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: " << filepath << std::endl << infoLog << std::endl;
    }

    link(vertexID, fragmentID);

}

void Shader::link(unsigned int vertex, unsigned int fragment){
    shaderID = glCreateProgram();
    glAttachShader(shaderID, vertex);
    glAttachShader(shaderID, fragment);
    glLinkProgram(shaderID);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::LINKING_FAILED: " << filepath << std::endl << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use(){
    if(!inUse){
        glUseProgram(shaderID);
        inUse = true;
    }
}

void Shader::unuse(){
    glUseProgram(0);
    inUse = false;
}

Shader::~Shader() {
    if (shaderID != 0) {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }
}


void Shader::uploadMatrix4(const char* varname, const Matrix4& mat4){
    GLint varLocation = glGetUniformLocation(shaderID, varname);
    use();
    glUniformMatrix4fv(varLocation, 1, GL_FALSE, mat4.m);
}

void Shader::uploadIntArr(const char* varname, const int* arr, int count){
    GLint varLocation = glGetUniformLocation(shaderID, varname);
    use();
    glUniform1iv(varLocation, count, arr);
}

unsigned int Shader::getID(){
    return shaderID;
}
