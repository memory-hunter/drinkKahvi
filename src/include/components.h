#ifndef DRINKKAHVI_COMPONENTS_H
#define DRINKKAHVI_COMPONENTS_H

#include <imgui.h>
#include <imgui_stdlib.h>
#include <filesystem>
#include <boost/property_tree/json_parser.hpp>

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
            static bool kahvi_dir_set = false;
            boost::property_tree::ptree root;
            if (std::filesystem::exists("config.json") && !kahvi_dir_set) {
                boost::property_tree::read_json("config.json", root);
                kahvi_dir = root.get<std::string>("kahvi_path");
                kahvi_dir_set = true;
            }
            ImGui::InputText("###kahvi_dir", &kahvi_dir);
            std::filesystem::path kahvi_path(kahvi_dir);
            if (!std::filesystem::is_directory(kahvi_path)) {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Invalid directory");
            }
            if (ImGui::Button("Set", ImVec2(120, 0))) {
                if (kahvi_dir[0] == '\"' && kahvi_dir[kahvi_dir.length() - 1] == '\"') {
                    kahvi_dir = kahvi_dir.substr(1, kahvi_dir.length() - 2);
                }
                root.put("kahvi_path", kahvi_dir);
                boost::property_tree::write_json("config.json", root);
                kahvi_dir_set = false;
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
    }
}

#endif //DRINKKAHVI_COMPONENTS_H
