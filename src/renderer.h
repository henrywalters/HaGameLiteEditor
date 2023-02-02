//
// Created by henry on 1/11/23.
//

#ifndef HAGAMELITEEDITOR_RENDERER_H
#define HAGAMELITEEDITOR_RENDERER_H

#include "hagame/graphics/renderPipeline.h"

class Renderer : public hg::graphics::RenderPipeline {
public:
    void onBeforeRender() override {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void onRender() override {

    }

    void onAfterRender() override {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
};

#endif //HAGAMELITEEDITOR_RENDERER_H
