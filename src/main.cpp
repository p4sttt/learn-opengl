#include "Logger.hpp"
#include "OpenGLModel.hpp"
#include "ShaderProgram.hpp"
#include "OpenGLRenderer.hpp"
#include "ProjectLoader.hpp"
#include "Window.hpp"

int main() {
    LOG_INFO("Starting program epta");

    Window window;
    OpenGLModel openGLModel;
    ShaderProgram shaderProgram;

    ProjectLoader::loadModel("res/model.obj", openGLModel);
    ProjectLoader::loadShaderProgram("res/vertex.glsl", "res/fragment.glsl",
                                     shaderProgram);

    OpenGLRenderer renderer(shaderProgram);
    renderer.AddOpenGLModel(openGLModel);

    window.setRenderer(renderer);
    window.Render();

    LOG_INFO("Program was successfully executed");
}
