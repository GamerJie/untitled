//
// Created by Jie on 2018/8/7.
//

#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H

#include "Const.h"
#include "Object.h"

class World;

namespace sf {
    class RenderWindow;
}

class Game : public Object {
public:
    Game();
    ~Game();

    void run();
    void pause();
    void resume();

    void exit();

	float getTime();
    Config getConfig();

private:
	float mTime = 0.0f;
	float timeScale = 1.0f;

    Config config;
    sf::RenderWindow* mWindow;
    std::shared_ptr<World> world;
    std::shared_ptr<spdlog::logger> console;

    void setup();
};

#endif //UNTITLED_GAME_H
