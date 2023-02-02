#include <memory>
#include <iostream>
#include "hagame/graphics/windows.h"
#include "hagame/utils/timer.h"
#include "hagame/utils/file.h"
#include "hagame/core/game.h"

#include "hagame/core/hg.h"

#include "imgui.h"
#include "imgui_demo.cpp"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "src/mainMenu.h"
#include "src/renderer.h"
#include "src/assets.h"

#include "src/scenes/editor.h"

using namespace hg;
using namespace hg::graphics;
using namespace hg::math;
using namespace hg::utils;

std::vector<std::unique_ptr<UIObject>> uiElements;

namespace hg {
    class HaGameEditor : public Game {
    public:

        HaGameEditor(std::string name) : Game(name) {}

        void onResize(Vec2i size) override {
            std::cout << size << "\n";
        }

        void onInit() override {

            auto standardVert = utils::f_read(ASSET_DIR + "shaders/standard.vert");
            auto testFrag = utils::f_read(ASSET_DIR + "shaders/test.frag");
            auto colorFrag = utils::f_read(ASSET_DIR + "shaders/color.frag");
            auto textureFrag = utils::f_read(ASSET_DIR + "shaders/texture.frag");
            auto vertex = Shader::LoadVertex(standardVert);
            auto testFragment = Shader::LoadFragment(testFrag);
            auto colorFragment = Shader::LoadFragment(colorFrag);
            auto textureFragment = Shader::LoadFragment(textureFrag);

            SHADERS.set("test", new ShaderProgram("sprite", vertex, testFragment));
            SHADERS.set("color", new ShaderProgram("sprite", vertex, colorFragment));
            SHADERS.set("texture", new ShaderProgram("sprite", vertex, textureFragment));

            uiElements.push_back(std::make_unique<MainMenu>());

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

            ImGui_ImplGlfw_InitForOpenGL(window()->window(), true);
            ImGui_ImplOpenGL3_Init("#version 300 es");

            scenes()->add<hg::Editor>("editor");
            scenes()->activate("editor");
        }

        void onUpdate(double dt) override {

            for (const auto& element : uiElements) {
                element->update(dt);
            }

            window()->title("FPS: " + std::to_string(1.0 / dt));
        }
    };
}

int main() {

    auto pipeline = Renderer();
    hg::HaGameEditor editor = hg::HaGameEditor("HaGame Editor");
    editor.renderPipeline(&pipeline);
    hg::HG::Run(&editor);

    return 0;
}
