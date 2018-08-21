//
// Created by Jie on 2018/8/10.
//

#include "Game.h"
#include "Editor.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Editor* Editor::mInstance = nullptr;

Editor::Editor() {
    console = spdlog::stdout_color_mt("Editor");
}

Editor::~Editor() {
    ImGui::SFML::Shutdown();

    if(Editor::mInstance == nullptr)
        return;

    delete Editor::mInstance;
	Editor::mInstance = nullptr;
}

Editor* Editor::instance() {
    if(Editor::mInstance == nullptr)
		Editor::mInstance = new Editor;

    return Editor::mInstance;
}

void Editor::init(sf::RenderWindow* window,Game* game, bool loadDefaultFont) {
    mGame = game;
    mWindow = window;
    ImGui::SFML::Init(*mWindow, loadDefaultFont);


    auto IO = ImGui::GetIO();
    IO.Fonts->Clear();
    IO.Fonts->AddFontFromFileTTF("../../res/fonts/Zpix.ttf", 20.f);
    // IO.Fonts->AddFontFromFileTTF("../../res/fonts/Zpix.ttf", 20.f, nullptr, IO.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    ImGui::SFML::UpdateFontTexture();
}

float zoom = 1.0f;
void Editor::processEvent(sf::Event _event) {
    ImGui::SFML::ProcessEvent(_event);

	auto view = mWindow->getView();

	if (_event.type == sf::Event::MouseWheelMoved) {

		zoom += _event.mouseWheel.delta / 10.f;
		view.zoom(zoom);

		mWindow->setView(view);

		console->info(zoom);

		if (_event.mouseWheel.delta > 0) { // scroll up

		}
		else {

		}
	}
}

void Editor::update(sf::Time dt) {
    ImGui::SFML::Update(*mWindow, dt);

    draw(dt.asSeconds());
    calcFps(dt.asSeconds());
}

void Editor::calcFps(float dt) {
	timer += dt;

	if (timer >= 1) {
		fps = frameIdx;

		timer--;
		frameIdx = 0;
	}
	else
		frameIdx++;
}

void Editor::render() {
    ImGui::SFML::Render(*mWindow);
	mTiledEditor.render(mWindow);
}

void Editor::draw(float dt) {
    ImGui::ShowDemoWindow();
    drawMenu(dt);

}

void Editor::drawMenu(float dt) {
    ImGui::BeginMainMenuBar();

    if(ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Open", "Ctrl+O")) {

        }
        if (ImGui::MenuItem("Save", "Ctrl+S")) {

        }

        ImGui::Separator();

        if (ImGui::MenuItem("Exit", "Alt+F4"))
            mGame->exit();

        ImGui::EndMenu();
    }

    if(ImGui::BeginMenu("Edit")){

        if(ImGui::MenuItem("Undo", "Ctrl+Z")){

        }

        if(ImGui::MenuItem("Redo", "Ctrl+Y")){

        }

        ImGui::Separator();

        if(ImGui::MenuItem("...")){

        }

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Windows")) {
        ImGui::MenuItem("...");

        ImGui::Separator();
        ImGui::MenuItem("Console", "Ctrl+L", &showConsole);
		ImGui::MenuItem("Animation Editor", "Ctrl+E", &showAnimationEditor);
		ImGui::MenuItem("Tiled Editor", "Ctrl+T", &showTileEditor);

        ImGui::EndMenu();
    }



	ImGui::SetCursorPosX(mGame->getConfig().width - 250.f);
	ImGui::Text(fmt::format("Time: {:.1f}s", mGame->getTime()).c_str());

	ImGui::SetCursorPosX(mGame->getConfig().width - 100.f);
    ImGui::Text(fmt::format("FPS: {}", fps).c_str());

    ImGui::EndMainMenuBar();

    if(showConsole)
        mConsole.Draw("Console", &showConsole);
    if(showAnimationEditor)
		mAnimationEditor.Draw("Animation Editor", &showAnimationEditor, dt);
	if (showTileEditor)
		mTiledEditor.Draw("Tiled Editor", &showTileEditor, dt);
}

void Editor::addLog(std::string log) {
	mConsole.AddLog(log.c_str());
}