//
// Created by Jie on 2018/8/8.
//

#ifndef UNTITLED_RESMANAGER_H
#define UNTITLED_RESMANAGER_H

#include "Const.h"
#include "Entity.h"
#include "TiledSet.h"

class ResManager : public Object{
public:
    ResManager();
    ~ResManager();

    static ResManager* instance();

    std::string dataPath();
    Config loadConfig(std::string);

	json loadJson(std::string);

	sol::table loadLuaData(std::string);

	void createFile(std::string path, std::string);

private:
    std::string mPath;
    std::shared_ptr<spdlog::logger> console;

    static ResManager* mInstance;
};

#endif //UNTITLED_RESMANAGER_H
