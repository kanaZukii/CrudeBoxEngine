#include "Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <vector>


void ImGUIexample(float deltaTime, float max, float min){
    ImGui::Begin("Hello Editor");
    ImGui::Text("DeltaTime: %.3f ms", deltaTime * 1000.0f);
    ImGui::Text("FPS: %.1f", 1.0f / deltaTime);
    ImGui::Text("MAX: %.1f", max);
    ImGui::Text("MIN: %.1f", min);
    ImGui::End();
}

int main() {
    CrudeBox::setWinTitle("Crude Box Editor");
    CrudeBox::setWinSize(1920,1080);
    CrudeBox::init();

     // ---- ImGui initialization ----
    GLFWwindow* windowPtr = glfwGetCurrentContext();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplGlfw_InitForOpenGL(windowPtr, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    float startTime = (float)glfwGetTime();
    float endTime = (float)glfwGetTime();
    float deltaTime = 0.0f;

    float FPS = 0.0f;
    float timer = 3.0f, minFPS = 120.0f, maxFPS = 0.0f;

    while(CrudeBox::isRunning()){
        
        CrudeBox::beginFrame();
        CrudeBox::update(deltaTime);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGUIexample(deltaTime, maxFPS, minFPS);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        CrudeBox::endFrame();

        endTime = (float)glfwGetTime();
        deltaTime = endTime - startTime;
        startTime = endTime;

        FPS = (float)(1/deltaTime);

        if(timer < 0.0f){
            if(FPS > maxFPS) maxFPS = FPS;
            if(FPS < minFPS) minFPS = FPS;
            timer = -1.0f;
        }

        timer -= deltaTime;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    CrudeBox::terminate();

    return 0;
}
