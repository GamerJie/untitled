//
// Created by Jie on 2018/8/4.
//

#include "World.h"
#include "Entity.h"

#include "Sprite.h"
#include "Transform.h"

Entity::Entity(World* world, int eid, const char* ename): mWorld(world), name(ename) {
    id = eid;
}

Entity::~Entity() {

}

Entity::Entity(World *world, int eid, sol::table data) : mWorld(world) {
	id = eid;

	sol::object name_t = data["name"];
	if (name_t.valid())
		name = name_t.as<std::string>();

	sol::table components_t = data["components"];
	if (components_t.valid())
		addLuaCom(components_t);
}

void Entity::destroy() {
    mWorld->destroyEntity(this);
}

const std::string Entity::tostring() const {
    return fmt::format("Entity ({}) [{}]", name, id);
}

World* Entity::getWorld() {
    return mWorld;
}

void Entity::addLuaCom(sol::table components_t) {
	for (auto& kv : components_t) {
		sol::object key = kv.first;
		sol::object val = kv.second;

		if (key.get_type() == sol::type::string) {
			std::string cname = key.as<std::string>();
			if (cname == "Transform")
				addComponent(new Transform(val));
			else if (cname == "Sprite")
				addComponent(new Sprite(val));
		}
	}
}

Component* Entity::getLuaCom(std::string cname) {
	if (cname == "Transform")
		return getComponent<Transform>();
	else if (cname == "Sprite")
		return getComponent<Sprite>();
	else
		return nullptr;
}