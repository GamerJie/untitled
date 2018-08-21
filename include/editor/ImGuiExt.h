//
// Created by Jie on 2018/8/10.
//

#ifndef UNTITLED_IMGUIEXT_H
#define UNTITLED_IMGUIEXT_H

#include <imgui.h>
#include <vector>
#include <string>

namespace ImGui {
	bool Combo(const char *label, int *currIndex, std::vector <std::string> &values);
	bool ListBox(const char *label, int *currIndex, std::vector <std::string> &values);

}

#endif //UNTITLED_IMGUIEXT_H
