//
// Created by henry on 1/11/23.
//

#ifndef HAGAMELITEEDITOR_RUNTIME_H
#define HAGAMELITEEDITOR_RUNTIME_H

#include <iostream>
#include "hagame/core/scene.h"
#include "hagame/graphics/primitives/quad.h"
#include "hagame/utils/random.h"
#include "hagame/graphics/renderPasses.h"

#include "../components/renderable.h"
#include "../assets.h"

struct Particle {
    hg::Vec3 velocity;
};

namespace hg {

    enum class RenderMode {
        Geometry,
    };

    class Runtime : public hg::Scene {
    public:

        void onInit() override {

            m_quad = std::make_unique<hg::graphics::primitives::Quad>(Vec2(15, 15));
            m_mesh = std::make_unique<hg::graphics::MeshInstance>(m_quad.get());

            updateMatrices();

            m_renderPasses.create(RenderMode::Geometry, game()->window()->size());

            for (int i = 0; i < 1000; i++) {
                auto entity = entities.add();
                hg::utils::Random rand;
                entity->transform.position[0] = rand.normal(game()->window()->size()[0] * 0.5, game()->window()->size()[0] * 0.15);
                entity->transform.position[1] = rand.normal(game()->window()->size()[1] * 0.5, game()->window()->size()[1] * 0.15);
                auto render = entity->addComponent<Renderable>();
                auto angle = m_random.real<float>(-math::PI, math::PI);
                auto particle = entity->addComponent<Particle>();
                particle->velocity = Vec3(cos(angle) * 10, sin(angle) * 10, 0);
                render->mesh = m_mesh.get();
                render->shader = SHADERS.get("test");
            }
        }

        void onUpdate(double dt) override {

            m_renderPasses.clear(RenderMode::Geometry, hg::graphics::Color::black());

            entities.forEach<Particle>([&](auto particle, auto entity) {
               entity->transform.move(particle->velocity * dt);
            });

            entities.forEach<Renderable>([&](auto renderable, auto entity) {
                renderable->shader->use();
                renderable->shader->setMat4("view", view);
                renderable->shader->setMat4("projection", proj);
                renderable->shader->setMat4("model", entity->transform.getModel());
                renderable->mesh->render();
            });

            m_renderPasses.render(RenderMode::Geometry);
            m_renderPasses.unbind(RenderMode::Geometry);

            m_renderPasses.activateTextures();

            ImGui::Begin("Renderer");
            auto rendererSize = ImGui::GetWindowSize();
            std::cout << m_renderPasses.get(RenderMode::Geometry)->texture->id << "\n";
            ImGui::Image((ImTextureID) m_renderPasses.get(RenderMode::Geometry)->texture->id, ImVec2(rendererSize.x - 10, rendererSize.y - 40), ImVec2(0, 0));
            ImGui::End();
        }

        hg::graphics::RenderPasses<RenderMode>* renderPasses() {
            return &m_renderPasses;
        }

    private:

        utils::Random m_random;

        std::unique_ptr<hg::graphics::MeshInstance> m_mesh;
        std::unique_ptr<hg::graphics::primitives::Quad> m_quad;

        hg::graphics::RenderPasses<RenderMode> m_renderPasses;

        Mat4 proj, view;

        void updateMatrices() {
            proj = Mat4::Orthographic(0, graphics::HD[0], 0, graphics::HD[1], -20, 20);
            view = Mat4::Identity();
            std::cout << proj << "\n";
        }

    };
}

#endif //HAGAMELITEEDITOR_RUNTIME_H
