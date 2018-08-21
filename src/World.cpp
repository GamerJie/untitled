//
// Created by Jie on 2018/8/7.
//

#include "World.h"
#include "ResManager.h"

#include <SFML/Graphics.hpp>

int World::mEntityIdx = 0;

World::World() {
    console = spdlog::stdout_color_mt("world");
}

World::~World() {

}

void World::setRender(sf::RenderTarget * render) {
    mRender = render;
}

void World::render(sf::Drawable *draw) {
    mRender->draw(*draw);
}

std::shared_ptr<World> World::create() {
    return std::make_shared<World>();
}

std::shared_ptr<Entity> World::createEntity() {
    return createEntity("No Name");
}

std::shared_ptr<Entity> World::createEntity(std::string name) {
    auto entity = std::make_shared<Entity>(this, ++ World::mEntityIdx, name.c_str());
    mEntities.push_back(entity);
    console->info("Create Entity OK {}", World::mEntityIdx);

	entity->setMediator(this);

    return entity;
}

std::shared_ptr<Entity> World::createEntityFromFile(std::string name) {
	auto data = ResManager::instance()->loadLuaData(name);
    auto entity = std::make_shared<Entity>(this, ++ World::mEntityIdx, data);
    mEntities.push_back(entity);
    console->info("Create Entity OK {}", World::mEntityIdx);

	entity->setMediator(this);

    return entity;
}

std::vector<std::shared_ptr<Entity>> World::all() {
    return mEntities;
}

void World::destroyEntity(Entity *entity) {
    for (auto it = mEntities.begin(); it != mEntities.end();) {
        if ((*it)->id == entity->id)
            it = mEntities.erase(it);
        else
            ++it;
    }
}

void World::update(float dt) {
    for (auto sys : mSystems)
        sys.second->update(dt);
}

void World::updateRender (float dt) {
    for (auto sys : mSystems)
        sys.second->updateRender(dt);
}

std::shared_ptr<Entity> World::find(int id) {
    for(auto entity : mEntities){
        if(entity->id == id)
            return entity;
    }
    return nullptr;
}

std::shared_ptr<Entity> World::find(const char * name) {
    for(auto entity : mEntities){
        if(entity->name == name)
            return entity;
    }
    return nullptr;
}

void World::sendMessage(std::string &message, Object *obj) {

}

void World::setRenter(Object *renter) {

};

void World::setLandlord(Object *landlord) {

};