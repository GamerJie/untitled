//
// Created by Jie on 2018/8/8.
//

#ifndef UNTITLED_LUAMANAGER_H
#define UNTITLED_LUAMANAGER_H

#include "Object.h"

class LuaEngine : public Object {
public:
    LuaEngine();
    ~LuaEngine();

    static LuaEngine* instance();

    sol::table loadData(std::string);

	void dofile(std::string);
	void dostring(std::string);

	void loadlibs();
	void registerClass();

	template<typename Func>
	void dostring(std::string code, Func cb) {
		auto pfr = mLua->safe_script(code, &sol::script_pass_on_error);
		if (!pfr.valid()) {
			sol::error err = pfr;
			cb(err.what());
		}
	}

    template <typename T>
    void registerMember(std::string name, T member){
        (*mLua)[name] = member;
    }

	template<typename Function>
	void registerFunction(std::string name, Function func)
	{
		mLua->set_function(name, func);
	}

private:
    sol::state* mLua;
    std::string mPath;

    static LuaEngine* mInstance;
    static std::shared_ptr<spdlog::logger> luaConsole;


    template <typename... Args>
    static void lua_print(const char* fmt, const Args &... args) {
        if(luaConsole == nullptr)
            luaConsole = spdlog::stdout_color_mt("lua");

        luaConsole->info(fmt, args...);
    }
};

#endif //UNTITLED_LUAMANAGER_H
