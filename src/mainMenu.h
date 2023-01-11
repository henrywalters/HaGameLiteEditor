//
// Created by henry on 12/29/22.
//

#ifndef HAGAMELITE_MAINMENU_H
#define HAGAMELITE_MAINMENU_H

#include "uiObject.h"
#include "imgui.h"

class MainMenu : public UIObject {
public:

    void update(double dt) override {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New Scene")) {}

                if (ImGui::MenuItem("Open Demo")) {
                    m_demoOpen = true;
                }

                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        if (m_demoOpen) {
            ImGui::ShowDemoWindow();
        }
    }

protected:
    [[nodiscard]] std::string toString() const override {
        return "MainMenu<" + std::to_string(id()) + ">";
    }

private:

    bool m_demoOpen = false;

};

#endif //HAGAMELITE_MAINMENU_H
