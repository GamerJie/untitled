//
// Created by Jie on 2018/8/8.
//

#ifndef UNTITLED_CONST_H
#define UNTITLED_CONST_H

#include "Object.h"

struct Config {
    std::string title;
    unsigned int width;
    unsigned int height;

    Config(){
        width = 800,
        height = 600,
        title = "Untitled";
    };

	Config(json data) {
		width = data["width"];
		height = data["height"];
		title = data["title"].dump();
	}
};

#endif //UNTITLED_CONST_H
