//
// Created by Jie on 2018/8/8.
//

#ifndef UNTITLED_LOGCONFIG_H
#define UNTITLED_LOGCONFIG_H

class Object;

std::ostream &operator<<(std::ostream &os, Object* object) {
    return os << object->tostring();
}


class basic_json;

std::ostream &operator<<(std::ostream &os, basic_json<>* object) {
	return os << object->dump();
}

#endif //UNTITLED_LOGCONFIG_H
