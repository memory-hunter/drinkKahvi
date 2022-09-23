#ifndef DRINKKAHVI_COMPONENTS_H
#define DRINKKAHVI_COMPONENTS_H

#include <imgui.h>
#include <imgui_stdlib.h>

struct popup_flags {
    bool about_popup = false;
    bool kahvi_dir_popup = false;
};

namespace components {
    inline void about_popup_handle() {
        ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2),
                                ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        if (ImGui::BeginPopup("About", ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("drinkKahvi");
            ImGui::Separator();
            ImGui::Text("A simple KahviBreak entry exporter to .zip for curations");
            ImGui::Text("Made by: memoryhunter");
            ImGui::EndPopup();
        }
    }

    inline void directory_modal_handle() {
        ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2),
                                ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        if (ImGui::BeginPopupModal("KahviBreak directory", nullptr,
                                   ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove)) {
            ImGui::Text("KahviBreak directory");
            ImGui::Separator();
            ImGui::Text("Please enter the KahviBreak directory:");
            static std::string kahvi_dir;
            ImGui::InputText("###kahvi_dir", &kahvi_dir);
            if (ImGui::Button("Set", ImVec2(120, 0))) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
    }
}

#endif //DRINKKAHVI_COMPONENTS_H
