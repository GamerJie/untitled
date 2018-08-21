//
// Created by Jie on 2018/8/4.
//

#ifndef UNTITLED_TRANSFORM_H
#define UNTITLED_TRANSFORM_H

#include "Component.h"

struct Vector2 : Object {
    float x;
    float y;

    Vector2(){
        x = 0;
        y = 0;
    }

    Vector2(float _x, float _y) : x(_x), y(_y) {}
};

class Transform : public Component {
public:
    Transform(){};
    Transform(sol::table data) {
        sol::table position_t = data["position"];
        if (position_t.get_type() == sol::type::table) {
            sol::object pos_x = position_t["x"];
            sol::object pos_y = position_t["y"];

            position = Vector2(pos_x.as<float>(), pos_y.as<float>());
        }


        sol::table scale_t = data["scale"];
        if (scale_t.get_type() == sol::type::table) {
            sol::object scale_x = scale_t["x"];
            sol::object scale_y = scale_t["y"];

            scale = Vector2(scale_x.as<float>(), scale_y.as<float>());
        }

        sol::object angle_t = data["angle"];
        if (angle_t.get_type() == sol::type::number)
            angle = angle_t.as<float>();
    }

    static Transform* get(Component* com) {
        return (Transform*)com;
    }

    float angle;
    Vector2 scale;
    Vector2 position;
};


#endif //UNTITLED_TRANSFORM_H
