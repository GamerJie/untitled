
#ifndef UNTITLED_TILEDMAP_H
#define UNTITLED_TILEDMAP_H

#include "Object.h"
#include "TiledSet.h"

struct TiledData {
	int index;
	TiledSet set;

	TiledData() {
		index = -1;
	}
};

class TiledMap : public Object {
public:
	unsigned int cellWidth;
	unsigned int cellHeight;

	TiledMap(int, int);

	void loadFormFile(std::string fileName);
	void save(std::string path);

	void setTiled(int x, int y, TiledData set);
	TiledData getTiled(int x, int y) const;
	void clear();
	
private:
	json mData;
	std::map<std::string, TiledData> tiledDatas;
};

#endif