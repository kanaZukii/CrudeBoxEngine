#pragma once

namespace CrudeBox {
    void setWinTitle(const char* title);
    void setWinSize(int width, int height);
    int getWinWidth();
    int getWinHeight();
    void init();
    bool isRunning();
    void update(float deltaTime);
    void beginFrame();
    void render();
    void endFrame();
    void terminate();
}
