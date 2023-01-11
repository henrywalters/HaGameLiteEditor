#include <memory>
#include <iostream>
#include "hagame/graphics/windows.h"
#include "hagame/utils/timer.h"
#include "hagame/core/game.h"

#include "hagame/core/hg.h"

#include "imgui.h"
#include "imgui_demo.cpp"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "src/mainMenu.h"

using namespace hg;
using namespace hg::graphics;
using namespace hg::math;
using namespace hg::utils;

#ifdef __EMSCRIPTEN__
const std::string ASSET_DIR = "./assets/";
#else
const std::string ASSET_DIR = "../assets/";
#endif

std::vector<std::unique_ptr<UIObject>> uiElements;

namespace hg {
    class Editor : public Game {
    public:

        Editor(std::string name) : Game(name) {}

        void onResize(Vec2i size) override {
            std::cout << size << "\n";
        }

        void onInit() override {

            std::cout << "INITIALIZING\n";

            uiElements.push_back(std::make_unique<MainMenu>());

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

            ImGui_ImplGlfw_InitForOpenGL(window()->window(), true);
            ImGui_ImplOpenGL3_Init("#version 300 es");
        }

        void onUpdate(double dt) override {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            window()->clear();

            for (const auto& element : uiElements) {
                element->update(dt);
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            window()->render();
        }
    };
}

int main() {

    hg::Editor editor = hg::Editor("HaGame Editor");
    hg::HG::Run(&editor);

    return 0;
}
