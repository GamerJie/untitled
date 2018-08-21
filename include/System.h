//
// Created by Jie on 2018/8/7.
//

#ifndef UNTITLED_SYSTEM_H
#define UNTITLED_SYSTEM_H

#include "Object.h"

class World;

class System : public Object {
public:
    virtual ~System() {};

    virtual void init(World* world) {
        mWorld = world;
        if (console == nullptr)
            console = spdlog::stdout_color_mt(tostring());
    };

    virtual void update(float){};
    virtual void updateRender(float){};

protected:
    World* mWorld;
};

#endif //UNTITLED_SYSTEM_H
