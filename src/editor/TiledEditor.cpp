
#include "Utils.h"
#include "ResManager.h"
#include "editor/ImGuiExt.h"
#include "editor/TiledEditor.h"

#include <imgui-SFML.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

TiledEditor::TiledEditor() {
	console = spdlog::stdout_color_mt("Tiled Editor");

	std::vector<std::string> list;
	Utils::DfsFolder(ResManager::instance()->dataPath() + "data/tiled/", list, "lua");
	for (auto str : list) {
		str = fmt::format("data/tiled/{}", str);
		fileList.push_back(str);
	}
	mSprite = new sf::Sprite;
	mTexture = new sf::Texture;
	mTexture->loadFromFile(fmt::format("{}images/sign.png", ResManager::instance()->dataPath()));
	mSprite->setTexture(*mTexture);
}

TiledEditor::~TiledEditor() {

}

void TiledEditor::render(sf::RenderWindow* window) {
	int x = sf::Mouse::getPosition(*window).x / 50;
	int y = sf::Mouse::getPosition(*window).y / 50;
	mSprite->setPosition(sf::Vector2f(50 * x, 50 * y));
	window->draw(*mSprite);
}

void TiledEditor::Draw(const char *title, bool *p_open, float dt) {
	ImGui::SetNextWindowSize(ImVec2(420, 600), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(title, p_open)) {
		ImGui::End();
		return;
	}

	if (selected != lastSelected)
		OnSelectChange();

	ImGui::Combo("Tiled Set", &selected, fileList);


	if(sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {

	}

	ImGui::End();
}

void TiledEditor::OnSelectChange() {

	lastSelected = selected;
}