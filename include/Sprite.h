//
// Created by Jie on 2018/8/7.
//

#ifndef UNTITLED_GRAPHICS_H
#define UNTITLED_GRAPHICS_H

#include "Component.h"
#include "ResManager.h"
#include "LuaEngine.h"

#include <SFML/Graphics.hpp>

struct AnimationData {
    std::string name;
    float timer;
    unsigned int length;
    std::vector<sf::IntRect> rects;
};

class Sprite : public Component {
public:
    Sprite() {};

	Sprite(std::string fileName) {
		sol::table data = ResManager::instance()->loadLuaData(fileName);
		if (data == sol::nil)
			return;

		sol::table components_t = data["components"];
		for (auto &kv : components_t) {
			sol::object key = kv.first;
			sol::object val = kv.second;

			if (key.get_type() == sol::type::string) {
				std::string cname = key.as<std::string>();
				if (cname == "Sprite") {
				    new (this) Sprite(val);
					// this->Sprite::Sprite(val);
				}
			}
		}
	}

	Sprite(sol::table data) {
		sol::object name_t = data["fileName"];
		std::string fileName = name_t.as<std::string>();

		mTexture.loadFromFile(fmt::format("../../res/{}", fileName));
		sprite.setTexture(mTexture);

		sol::object rectObj = data["rect"];
		if (rectObj.get_type() == sol::type::table) {
			auto rect = rectObj.as<sol::table>();
			sol::object rectX = rect[1];
			sol::object rectY = rect[2];
			sol::object rectW = rect[3];
			sol::object rectH = rect[4];
			sprite.setTextureRect(
				sf::IntRect(rectX.as<int>(), rectY.as<int>(), rectW.as<int>(), rectH.as<int>()));

			sprite.setOrigin(sf::Vector2f(rectW.as<int>() / 2, rectH.as<int>() / 2));

			auto size = mTexture.getSize();
			int row = size.x / rectW.as<int>();
			int line = size.y / rectH.as<int>();

			std::vector<sf::IntRect> animationRects;
			for (int i = 0; i < line; ++i) {
				for (int j = 0; j < row; ++j) {
					animationRects.push_back(sf::IntRect(j * rectW.as<int>(), i * rectH.as<int>(), rectW.as<int>(), rectH.as<int>()));
				}
			}

			sol::object
				animationsObj = data["animations"];
			hasAnimations = animationsObj.get_type() == sol::type::table;
			if (hasAnimations) {
				bool isFirst = true;
				auto animations = animationsObj.as<sol::table>();
				for (auto &kv : animations) {
					sol::object key = kv.first;
					sol::object val = kv.second;
					if (key.get_type() == sol::type::string) {
						if (val.get_type() == sol::type::table) {
							auto aniName = key.as<std::string>();

							sol::table animation = val.as<sol::table>();
							sol::object start = animation["start"];
							sol::object length = animation["length"];
							sol::object time_o = animation["timer"];
							AnimationData data;
							data.name = aniName;
							data.timer = time_o.as<float>();
							data.length = length.as<int>();

							for (unsigned int i = 0; i < data.length; ++i) {
								data.rects.push_back(animationRects[start.as<int>() + i]);
							}

							animationList[aniName] = data;

							if (isFirst) {
								update(aniName);
								isFirst = false;
							}
						}
					}
				}
			}
		}
	};

	static Sprite* get(Component* com) {
		return (Sprite*)com;
	}

    void update(std::string animation){
		if (curAnimation == animation)return;
        curAnimation = animation;
        curData = animationList[curAnimation];

        timer = 0;
        curIndex = 0;
        if(hasAnimations)
            sprite.setTextureRect(curData.rects[curIndex]);
    }

    void update(const char* animation, unsigned int id){
        curAnimation = animation;
        curData = animationList[curAnimation];

        timer = 0;
        curIndex = id;
        if(hasAnimations)
            sprite.setTextureRect(curData.rects[curIndex]);
    }

    void next(float dt){
        if(!hasAnimations)
            return;

        timer += dt;
        if(timer >= curData.timer) {
            timer = 0;
            curIndex++;
            if(curIndex >= curData.length)
                curIndex = 0;

            sprite.setTextureRect(curData.rects[curIndex]);
        }
    }

    sf::Sprite sprite;
	std::string curAnimation;
	unsigned int curIndex = 0;
	bool hasAnimations = false;
    std::map<std::string, AnimationData> animationList;

private:
    float timer;
    sf::Texture mTexture;
    AnimationData curData;
};

#endif //UNTITLED_GRAPHICS_H
