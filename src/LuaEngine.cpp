//
// Created by Jie on 2018/8/8.
//

#include "LuaEngine.h"
#include "ResManager.h"

#include "Utils.h"
#include "World.h"
#include "Entity.h"
#include "Sprite.h"
#include "Transform.h"

LuaEngine* LuaEngine::mInstance = nullptr;

int exception_handler(lua_State* L, sol::optional<const std::exception&> maybe_exception, sol::string_view description) {
	// L is the lua state, which you can wrap in a state_view if necessary
	// maybe_exception will contain exception, if it exists
	// description will either be the what() of the exception or a description saying that we hit the general-case catch(...)
	std::cout << "An exception occurred in a function, here's what it says ";
	if (maybe_exception) {
		std::cout << "(straight from the exception): ";
		const std::exception& ex = *maybe_exception;
		std::cout << ex.what() << std::endl;
	}
	else {
		std::cout << "(from the description parameter): ";
		std::cout.write(description.data(), description.size());
		std::cout << std::endl;
	}

	// you must push 1 element onto the stack to be 
	// transported through as the error object in Lua
	// note that Lua -- and 99.5% of all Lua users and libraries -- expects a string
	// so we push a single string (in our case, the description of the error)
	return sol::stack::push(L, description);
}

LuaEngine::LuaEngine() {
    mLua = new sol::state;
    mLua->open_libraries();
    mPath = ResManager::instance()->dataPath();
    mLua->script(fmt::format("package.path = package.path .. \";{}/?.lua;\"", mPath));
	mLua->set_exception_handler(&exception_handler);

    console = spdlog::stdout_color_mt("LuaEngine");
    registerClass();
}

LuaEngine::~LuaEngine() {
    if(LuaEngine::mInstance == nullptr)
        return;

    delete LuaEngine::mInstance;
	LuaEngine::mInstance = nullptr;
}

LuaEngine* LuaEngine::instance() {
    if(LuaEngine::mInstance == nullptr)
		LuaEngine::mInstance = new LuaEngine;

    return LuaEngine::mInstance;
}

void LuaEngine::loadlibs() {
	console->info("load libs ...");
	std::vector<std::string> list;
	Utils::DfsFolder(fmt::format("{}libs", mPath), list, "lua");
	for (auto s : list) {
		auto str = fmt::format("{}libs/{}", mPath, s);
		auto pfr = mLua->safe_script_file(str, &sol::script_pass_on_error);

		if (!pfr.valid()) {
			sol::error err = pfr;
			console->error(err.what());
			break;
		}
		console->info(str);
	}
	console->info("load over .");
}

sol::table LuaEngine::loadData(std::string fileName) {
	auto data = mLua->safe_script_file(fileName, &sol::script_pass_on_error);
	if (!data.valid()) {
		sol::error err = data;
		console->error(err.what());
		return sol::nil;
	}

    return data;
}

void LuaEngine::dostring(std::string code) {
    auto pfr = mLua->safe_script(code, &sol::script_pass_on_error);
	if (!pfr.valid()) {
		sol::error err = pfr;
		console->error(err.what());
	}
}

void LuaEngine::dofile(std::string fileName) {
	auto path = fmt::format("{}{}", mPath, fileName);
	auto pfr = mLua->safe_script_file(path, &sol::script_pass_on_error);
	if (!pfr.valid()) {
		sol::error err = pfr;
		console->error(err.what());
		return;
	}
}

void LuaEngine::registerClass() {
	mLua->new_usertype<Entity>(
		"Entity",
		"name", &Entity::name,
		"getWorld", &Entity::getWorld,
		"addCom", &Entity::addLuaCom,
		"getCom", &Entity::getLuaCom,
		"destroy", &Entity::destroy
		);

	mLua->new_usertype<World>(
		"World",
		"create", sol::overload(sol::resolve<std::shared_ptr<Entity>()>(&World::createEntity)),
		"find", sol::overload(sol::resolve<std::shared_ptr<Entity>(const char*)>(&World::find)),
		"destroy", &World::destroyEntity
		);

	mLua->new_usertype<Sprite>(
		"Sprite",
		sol::constructors<Sprite(), Sprite(sol::table)>(),
		"update", sol::resolve<void(std::string)>(&Sprite::update),
		"get", &Sprite::get
		);

	mLua->new_usertype<Vector2>(
		"Vector2",
		"x", &Vector2::x,
		"y", &Vector2::y
		);

	mLua->new_usertype<Component>(
		"Component"
		);

	mLua->new_usertype<Transform>(
		"Transform",
		sol::constructors<Transform(), Transform(sol::table)>(),
		"position", &Transform::position,
		"scale", &Transform::scale,
		"angle", &Transform::angle,
		"get", &Transform::get
		);

	mLua->set("SpriteCom", "Sprite");
	mLua->set("TransformCom", "Transform");

	sol::table key = mLua->create_named_table("Key");
	key.set("A", sf::Keyboard::A);
	key.set("B", sf::Keyboard::B);
	key.set("C", sf::Keyboard::C);
	key.set("D", sf::Keyboard::D);
	key.set("E", sf::Keyboard::E);
	key.set("F", sf::Keyboard::F);
	key.set("G", sf::Keyboard::G);
	key.set("H", sf::Keyboard::H);
	key.set("I", sf::Keyboard::I);
	key.set("J", sf::Keyboard::J);
	key.set("K", sf::Keyboard::K);
	key.set("L", sf::Keyboard::L);
	key.set("M", sf::Keyboard::M);
	key.set("N", sf::Keyboard::N);
	key.set("O", sf::Keyboard::O);
	key.set("P", sf::Keyboard::P);
	key.set("Q", sf::Keyboard::Q);
	key.set("R", sf::Keyboard::R);
	key.set("S", sf::Keyboard::S);
	key.set("T", sf::Keyboard::T);
	key.set("U", sf::Keyboard::U);
	key.set("V", sf::Keyboard::V);
	key.set("W", sf::Keyboard::W);
	key.set("X", sf::Keyboard::X);
	key.set("Y", sf::Keyboard::Y);
	key.set("Z", sf::Keyboard::Z);
	key.set("Num0", sf::Keyboard::Num0);
	key.set("Num1", sf::Keyboard::Num1);
	key.set("Num2", sf::Keyboard::Num2);
	key.set("Num3", sf::Keyboard::Num3);
	key.set("Num4", sf::Keyboard::Num4);
	key.set("Num5", sf::Keyboard::Num5);
	key.set("Num6", sf::Keyboard::Num6);
	key.set("Num7", sf::Keyboard::Num7);
	key.set("Num8", sf::Keyboard::Num8);
	key.set("Num9", sf::Keyboard::Num9);
	key.set("Escape", sf::Keyboard::Escape);
	key.set("LControl", sf::Keyboard::LControl);
	key.set("LShift", sf::Keyboard::LShift);
	key.set("LAlt", sf::Keyboard::LAlt);
	key.set("LSystem", sf::Keyboard::LSystem);
	key.set("RControl", sf::Keyboard::RControl);
	key.set("RShift", sf::Keyboard::RShift);
	key.set("RAlt", sf::Keyboard::RAlt);
	key.set("RSystem", sf::Keyboard::RSystem);
	key.set("Menu", sf::Keyboard::Menu);
	key.set("LBracket", sf::Keyboard::LBracket);
	key.set("RBracket", sf::Keyboard::RBracket);
	key.set("Semicolon", sf::Keyboard::Semicolon);
	key.set("Comma", sf::Keyboard::Comma);
	key.set("Period", sf::Keyboard::Period);
	key.set("Quote", sf::Keyboard::Quote);
	key.set("Slash", sf::Keyboard::Slash);
	key.set("Backslash", sf::Keyboard::Backslash);
	key.set("Tilde", sf::Keyboard::Tilde);
	key.set("Equal", sf::Keyboard::Equal);
	key.set("Hyphen", sf::Keyboard::Hyphen);
	key.set("Space", sf::Keyboard::Space);
	key.set("Enter", sf::Keyboard::Enter);
	key.set("Backspace", sf::Keyboard::Backspace);
	key.set("Tab", sf::Keyboard::Tab);
	key.set("PageUp", sf::Keyboard::PageUp);
	key.set("PageDown", sf::Keyboard::PageDown);
	key.set("End", sf::Keyboard::End);
	key.set("Home", sf::Keyboard::Home);
	key.set("Insert", sf::Keyboard::Insert);
	key.set("Delete", sf::Keyboard::Delete);
	key.set("Add", sf::Keyboard::Add);
	key.set("Subtract", sf::Keyboard::Subtract);
	key.set("Multiply", sf::Keyboard::Multiply);
	key.set("Divide", sf::Keyboard::Divide);
	key.set("Left", sf::Keyboard::Left);
	key.set("Right", sf::Keyboard::Right);
	key.set("Up", sf::Keyboard::Up);
	key.set("Down", sf::Keyboard::Down);
	key.set("Numpad0", sf::Keyboard::Numpad0);
	key.set("Numpad1", sf::Keyboard::Numpad1);
	key.set("Numpad2", sf::Keyboard::Numpad2);
	key.set("Numpad3", sf::Keyboard::Numpad3);
	key.set("Numpad4", sf::Keyboard::Numpad4);
	key.set("Numpad5", sf::Keyboard::Numpad5);
	key.set("Numpad6", sf::Keyboard::Numpad6);
	key.set("Numpad7", sf::Keyboard::Numpad7);
	key.set("Numpad8", sf::Keyboard::Numpad8);
	key.set("Numpad9", sf::Keyboard::Numpad9);
	key.set("F1", sf::Keyboard::F1);
	key.set("F2", sf::Keyboard::F2);
	key.set("F3", sf::Keyboard::F3);
	key.set("F4", sf::Keyboard::F4);
	key.set("F5", sf::Keyboard::F5);
	key.set("F6", sf::Keyboard::F6);
	key.set("F7", sf::Keyboard::F7);
	key.set("F8", sf::Keyboard::F8);
	key.set("F9", sf::Keyboard::F9);
	key.set("F10", sf::Keyboard::F10);
	key.set("F11", sf::Keyboard::F11);
	key.set("F12", sf::Keyboard::F12);
	key.set("F13", sf::Keyboard::F13);
	key.set("F14", sf::Keyboard::F14);
	key.set("F15", sf::Keyboard::F15);
	key.set("Pause", sf::Keyboard::Pause);

	registerFunction("key_down", [](sf::Keyboard::Key code)->bool {
		return sf::Keyboard::isKeyPressed(code);
	});


	//    mLua->set_function("log", LuaManager::lua_print);
}