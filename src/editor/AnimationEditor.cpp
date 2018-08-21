//
// Created by Jie on 2018/8/10.
//

#include "Entity.h"
#include "Utils.h"
#include "ResManager.h"
#include "editor/ImGuiExt.h"
#include "editor/AnimationEditor.h"

#include <fstream>
#include <iostream>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>

AnimationEditor::AnimationEditor() {
    console = spdlog::stdout_color_mt("Animation Editor");

    std::vector<std::string> list;
    Utils::DfsFolder(ResManager::instance()->dataPath() + "data/entity/", list, "lua");
    for (auto str : list) {
        str = fmt::format("data/entity/{}", str);
        fileList.push_back(str);
    }
}

AnimationEditor::~AnimationEditor() {
    fileList.clear();
}

void AnimationEditor::Draw(const char *title, bool *p_open, float dt) {
    ImGui::SetNextWindowSize(ImVec2(420, 600), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(title, p_open)) {
        ImGui::End();
        return;
    }

    if(selected != lastSelected)
        OnSelectChange();

    if(animaSelected != lastAnimaSelected)
        OnAnimationChange();

    ImGui::Image(sprite->sprite, sf::Vector2f(256, 256));
    sprite->next(dt);

    ImGui::Combo("Entity", &selected, fileList);

    ImGui::Combo("Animation", &animaSelected, animaList);


    ImGui::End();
}

void AnimationEditor::OnSelectChange() {
    sprite = new Sprite(fileList[selected]);

    animaList.clear();
    for (auto str: sprite->animationList)
        animaList.push_back(str.second.name);

    lastSelected = selected;
}

void AnimationEditor::OnAnimationChange() {
    if(animaList.size() <= 0)
        return;

    sprite->update(animaList[animaSelected]);

    lastAnimaSelected = animaSelected;
}