#include "Logger.hpp"
#include "App.hpp"
#include "ProjectLoader.hpp"
#include "Graphics.hpp"

int main() {
    App::Window window = App::Window();

    ProjectLoader &loader = ProjectLoader::GetInstance();
    Graphics::Model model = loader.LoadModel();
    Graphics::ShaderProgram shaderProgram = loader.LoadShaderProgram();

    Graphics::Renderer renderer = Graphics::Renderer(model, shaderProgram);
    window.SetRenderer(&renderer);
    window.Render();

    LOG_INFO << "Program was successfully executed" << '\n';
}
