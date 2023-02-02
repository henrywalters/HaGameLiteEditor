//
// Created by henry on 1/29/23.
//

#ifndef HAGAMELITEEDITOR_EDITOR_H
#define HAGAMELITEEDITOR_EDITOR_H


#include <iostream>
#include "hagame/core/scene.h"
#include "hagame/graphics/primitives/quad.h"
#include "hagame/utils/random.h"
#include "hagame/graphics/renderPasses.h"

#include "../components/renderable.h"
#include "../assets.h"

#include "runtime.h"


namespace hg {

    class Editor : public hg::Scene {
    public:

        void onInit() override {
            //m_runtime = (Runtime*) game()->scenes()->add<Runtime>("runtime");
        }

        void onUpdate(double dt) override {

            ImGui::Begin("Renderer");
            auto rendererSize = ImGui::GetWindowSize();

            /*ImGui::Image(
                    (ImTextureID) m_runtime->renderPasses()->get(RenderMode::Geometry)->texture->id,
                    ImVec2(rendererSize.x - 10, rendererSize.y - 40),
                    ImVec2(0, 0)
            );
            */
            ImGui::End();
        }

    private:

        utils::Random m_random;

        std::unique_ptr<hg::graphics::MeshInstance> m_mesh;
        std::unique_ptr<hg::graphics::primitives::Quad> m_quad;

        hg::graphics::RenderPasses<RenderMode> m_renderPasses;

        Runtime* m_runtime;

        Mat4 proj, view;

        void updateMatrices() {
            proj = Mat4::Orthographic(0, graphics::HD[0], 0, graphics::HD[1], -20, 20);
            view = Mat4::Identity();
            std::cout << proj << "\n";
        }

    };
}
#endif //HAGAMELITEEDITOR_EDITOR_H
