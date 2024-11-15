#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Graphics.hpp"

namespace App {

void InitializeGLFW();

class Window {
  private:
    GLFWwindow *window;
    Graphics::Renderer *renderer;

  public:
    Window();
    Window(Graphics::Renderer *renderer);
    ~Window();

    void SetRenderer(Graphics::Renderer *renderer);
    GLFWwindow *GetGLFWwindow();

    void Update();
    void Render();
};

class EventHandler {
  private:
    Window &window;

    static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action,
                            int mods);
    static void ErrorCallback(int error, const char *description);

  public:
    EventHandler(Window &window);
    ~EventHandler();

    void HandleEvents();
};

} // namespace App