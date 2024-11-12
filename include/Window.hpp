#include <GLFW/glfw3.h>
#include "OpenGLRenderer.hpp"

#ifndef WINDOW_HPP
#define WINDOW_HPP

class Window {
  private:
    GLFWwindow *window;
    OpenGLRenderer renderer;

    static void FramebufferSizeCallback(GLFWwindow *window, int width,
                                        int height);
    static void KeyCallback(GLFWwindow *window, int key, int scancode,
                            int action, int mods);

  public:
    Window();
    ~Window();

    void setRenderer(OpenGLRenderer &renderer);

    void Render();
};

#endif
