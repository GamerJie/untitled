
#include "TiledSet.h"
#include "ResManager.h"

#include <SFML/Graphics.hpp>

TiledSet::TiledSet() {

}

void TiledSet::loadFormFile(std::string path) {
	filePath = path;
	auto sPath = fmt::format("{}{}",ResManager::instance()->dataPath(), filePath);
	mTexture.loadFromFile(sPath);
}

std::string TiledSet::getPath() const {
	return filePath;
}

sf::Sprite* TiledSet::get(int id) {
	sf::Sprite* sp = new sf::Sprite;
	sp->setTexture(mTexture);
	sp->setTextureRect(tiledSet[id]);
	return sp;
}