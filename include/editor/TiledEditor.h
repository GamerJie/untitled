
#ifndef UNTITLED_TILEDEDITOR_H
#define UNTITLED_TILEDEDITOR_H

#include "Object.h"
#include "TiledMap.h"

namespace sf {
	class Sprite;
	class Texture;
	class RenderWindow;
}

class TiledEditor : public Object {
public:
	TiledEditor();
	~TiledEditor();

	void render(sf::RenderWindow*);
	void Draw(const char *title, bool *p_open, float dt);

private:
	int selected = 0;
	int lastSelected = -1;
	std::vector<std::string> fileList;

	sf::Texture* mTexture;
	sf::Sprite* mSprite;

	void OnSelectChange();
};


#endif