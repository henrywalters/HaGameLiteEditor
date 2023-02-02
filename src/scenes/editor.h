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

            m_renderer.scene(this);
        }

        void onUpdate(double dt) override {

            m_renderer.clear();

            ImGui::Begin("Renderer");
            auto renderSize = ImGui::GetWindowSize();

            m_renderer.render(hg::Vec2i(renderSize[0] / 6, renderSize[1] / 6));

            ImGui::Image(
                    (ImTextureID) m_renderer.outputTexture()->id,
                    ImVec2(renderSize.x - 10, renderSize.y - 40),
                    ImVec2(0, 0)
            );

            ImGui::End();

            m_renderer.cleanup();
        }

    private:

        Renderer m_renderer;
        hg::graphics::RenderPasses<RenderMode> m_renderPasses;

        utils::Random m_random;

        std::unique_ptr<hg::graphics::MeshInstance> m_mesh;
        std::unique_ptr<hg::graphics::primitives::Quad> m_quad;



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
