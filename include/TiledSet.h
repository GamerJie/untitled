
#ifndef UNTITLED_TILEDSET_H
#define UNTITLED_TILEDSET_H

#include "Object.h"

#include <SFML/Graphics.hpp>

class TiledSet : public Object {
public:
	TiledSet();

	void loadFormFile(std::string path);

	sf::Sprite* get(int);

	std::string getPath() const;

private:
	sf::Texture mTexture;
	std::string filePath;
	std::map<int, sf::IntRect> tiledSet;
};

#endif