
#include "TiledMap.h"
#include "ResManager.h"

TiledMap::TiledMap(int width, int height)
	:cellWidth(width), cellHeight(height) {
	mData = json::array();
}

void TiledMap::loadFormFile(std::string fileName) {
	mData = ResManager::instance()->loadJson(fileName);
}

void TiledMap::save(std::string path) {
	auto str = mData.dump(4);
	ResManager::instance()->createFile(path, str);
}

void TiledMap::setTiled(int x, int y, TiledData set) {	
	auto data_j = json::object();
	data_j["id"] = set.index;
	data_j["x"] = x;
	data_j["y"] = y;
	data_j["tiled_set"] = set.set.getPath();
	mData.push_back(data_j);

	auto key = fmt::format("{}_{}", x, y);
	tiledDatas[key] = set;
}

TiledData TiledMap::getTiled(int x, int y) const {
	auto key = fmt::format("{}_{}", x, y);
	auto iter = tiledDatas.find(key);
	if (iter != tiledDatas.end())
		return iter->second;
	else
		return TiledData();
}

void TiledMap::clear() {
	tiledDatas.clear();
}