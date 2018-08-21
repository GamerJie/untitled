//
// Created by Jie on 2018/8/8.
//

#ifndef UNTITLED_LUAMANAGER_H
#define UNTITLED_LUAMANAGER_H

#include "Object.h"

class LuaManager : public Object {
public:
    LuaManager();
    ~LuaManager();

    static LuaManager* instance();

    sol::table loadData(const char*);
    sol::table loadEntity(const char *);
    //std::map<std::string, lData> loadData(const char*);

    void dostring(std::string);

    template <typename T>
    void registerMember(std::string name, T member){
        (*mLua)[name] = member;
    }

    void registerClass();

private:
    sol::state* mLua;
    std::string mPath;

    static LuaManager* mInstance;
    static std::shared_ptr<spdlog::logger> luaConsole;


    template <typename... Args>
    static void lua_print(const char* fmt, const Args &... args) {
        if(luaConsole == nullptr)
            luaConsole = spdlog::stdout_color_mt("lua");

        luaConsole->info(fmt, args...);
    }
};

#endif //UNTITLED_LUAMANAGER_H
