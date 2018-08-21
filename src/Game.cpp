//
// Created by Jie on 2018/8/7.
//

#include "Game.h"
#include "World.h"

#include "Editor.h"
#include "ResManager.h"

#include "InputSystem.h"
#include "RenderSystem.h"

#include "LuaEngine.h"

#include "Transform.h"

#include "Utils.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

Game::Game() {
	console = spdlog::stdout_color_mt("Game");
	config = ResManager::instance()->loadConfig("res");
	mWindow = new sf::RenderWindow(sf::VideoMode(config.width, config.height), config.title,
		sf::Style::Titlebar | sf::Style::Close);
	Editor::instance()->init(mWindow, this, false);
	mWindow->setFramerateLimit(60);

	world = World::create();
	world->setRender(mWindow);
	LuaEngine::instance()->registerMember("world", world);
	LuaEngine::instance()->registerFunction("log", [](std::string str)->void {
		Editor::instance()->addLog(str);
	});

	LuaEngine::instance()->loadlibs();

	setup();
}

Game::~Game() {
	delete mWindow;
	mWindow = nullptr;
}

void Game::setup(){
    world->addSystem<InputSystem>();
    world->addSystem<RenderSystem>();

	LuaEngine::instance()->dofile("main.lua");
	LuaEngine::instance()->dostring("setup()");
}

Config Game::getConfig() {
    return config;
}

void Game::run() {
	sf::Clock _time;
    sf::Clock _clock;
    sf::Event _event {};
    while (mWindow->isOpen()) {
        if (mWindow->pollEvent(_event)) {
			Editor::instance()->processEvent(_event);

            if (_event.type == sf::Event::Closed)
                mWindow->close();
        }

        auto time = _clock.restart();
		Editor::instance()->update(time);
		mTime += time.asSeconds() * timeScale;
        world->update(time.asSeconds() * timeScale);

		LuaEngine::instance()->dostring(fmt::format("update({})", time.asSeconds() * timeScale));

        mWindow->clear(sf::Color(133,133,133));
        world->updateRender(time.asSeconds() * timeScale);
		Editor::instance()->render();
        mWindow->display();
    }
}

float Game::getTime() {
	return mTime;
}

void Game::pause() {
	timeScale = 0;
}

void Game::resume() {
	timeScale = 1;
}

void Game::exit(){
    mWindow->close();
}