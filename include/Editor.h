//
// Created by Jie on 2018/8/10.
//

#ifndef UNTITLED_EDITOR_H
#define UNTITLED_EDITOR_H

#include "Object.h"

#include "editor/TiledEditor.h"
#include "editor/ConsoleEditor.h"
#include "editor/AnimationEditor.h"

#include <imgui.h>
#include <imgui-SFML.h>

class Game;

class Editor : public Object {
public:
	Editor();
    ~Editor();

    static Editor* instance();

    void init(sf::RenderWindow* window, Game* game, bool loadDefaultFont = true);
    void processEvent(sf::Event event);
    void update(sf::Time dt);
	void render();

	void addLog(std::string);

private:
    Game* mGame;
    sf::RenderWindow* mWindow;
    std::shared_ptr<spdlog::logger> console;

    int fps = 0;
    float timer = 0;
    unsigned int frameIdx;

    bool showConsole = false;
    ConsoleEditor mConsole;
    bool showAnimationEditor = false;
	AnimationEditor mAnimationEditor;
	bool showTileEditor = false;
	TiledEditor mTiledEditor;

    static Editor* mInstance;

    void draw(float);
    void drawMenu(float);

    void calcFps(float);
};

#endif //UNTITLED_EDITOR_H
