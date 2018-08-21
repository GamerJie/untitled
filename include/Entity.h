//
// Created by Jie on 2018/8/4.
//

#ifndef UNTITLED_ENTITY_H
#define UNTITLED_ENTITY_H

#include "Component.h"

class World;

class Entity: public Object {
public:
    Entity(World*, int, sol::table data);
    Entity(World*, int, const char* name = nullptr);
    ~Entity();

    std::string name = "";

    // Add a compoent with new
    template<typename T>
    T *addComponent(){
        auto type = std::type_index(typeid(T));
        mComponents[type] = new T;
        return dynamic_cast<T*>(mComponents[type]);
    }

    // Add a component with a instance
    template<typename T>
    void addComponent(T * com){
        auto type = std::type_index(typeid(T));
        mComponents[type] = com;
    }

    // Get a component by type
    template<typename T>
    T *getComponent(){
        auto it = mComponents.find(std::type_index(typeid(T)));
        if (it != mComponents.end()) {
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
	}

	void addLuaCom(sol::table);
	Component* getLuaCom(std::string);

    void destroy();
    const std::string tostring() const;
    World* getWorld();

private:
    World* mWorld;
    std::map<std::type_index, Component*> mComponents;
};

#endif //UNTITLED_ENTITY_H
