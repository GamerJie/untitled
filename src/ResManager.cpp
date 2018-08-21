//
// Created by Jie on 2018/8/8.
//

#include "Utils.h"
#include "LuaEngine.h"
#include "ResManager.h"

#include <sstream>
#include <fstream>

ResManager* ResManager::mInstance = nullptr;

ResManager::ResManager() {
    console = spdlog::stdout_color_mt("ResManager");
}

ResManager::~ResManager() {
    if(ResManager::mInstance == nullptr)
        return;

    delete ResManager::mInstance;
    ResManager::mInstance = nullptr;
}

ResManager* ResManager::instance() {
    if(ResManager::mInstance == nullptr)
        ResManager::mInstance = new ResManager;

    return ResManager::mInstance;
}

std::string ResManager::dataPath() {
    return mPath;
}

Config ResManager::loadConfig(std::string resDir) {
    char str[256];
    mPath = getcwd(str, 256);
    Utils::UPDir(mPath);
    mPath = mPath + "/" + resDir + "/";

    if(!Utils::DirExists(mPath)) {
        Utils::UPDir(mPath);

        Utils::UPDir(mPath);
        Utils::UPDir(mPath);

        mPath = mPath + "/" + resDir + "/";
        if(!Utils::DirExists(mPath))
            console->error("DataPath : ./{} and {} both not exit !", resDir, mPath);
    }

    console->info("Resources Path Set With: {}", mPath);

	auto data = ResManager::instance()->loadJson("config.json");
	if (data == nullptr) {
		console->error("config load failed !");
		return Config();
	}

    return Config(data);
}

json ResManager::loadJson(std::string fileName) {
	std::ifstream fs(fmt::format("{}{}", mPath, fileName));
	std::stringstream buffer;
	buffer << fs.rdbuf();
	std::string contents(buffer.str());
	if (!json::accept(contents)) {
		console->error("{} is not rigth json file !", fileName);
		return nullptr;
	}
	else
		return json::parse(contents);
}

sol::table ResManager::loadLuaData(std::string fileName) {
	auto path = fmt::format("{}{}", mPath, fileName);
	console->info("load lua data: {}", path);
	return LuaEngine::instance()->loadData(path);
}

void ResManager::createFile(std::string path, std::string str) {
	auto filePath = fmt::format("{}{}", mPath, path);
	ofstream in;
	in.open(filePath, ios::trunc);
	in << str;
	in.close();//¹Ø±ÕÎÄ¼þ
}