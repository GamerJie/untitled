//
// Created by Jie on 2018/8/7.
//

#ifndef UNTITLED_WORLD_H
#define UNTITLED_WORLD_H

#include "Entity.h"
#include "System.h"
#include "Mediator.h"

namespace sf {
    class RenderTarget;
    class Drawable;
}

class World : public Object, public Mediator {
public:
    static std::shared_ptr<World> create();

    World();
    ~World();

    template<typename T>
    T *addSystem() {
        auto type = std::type_index(typeid(T));
        mSystems[type] = new T;
        mSystems[type]->init(this);
        return dynamic_cast<T *>(mSystems[type]);
    }

    template<typename T>
    void addSystem(T *sys) {
        sys->init(this);
        auto type = std::type_index(typeid(T));
        mSystems[type] = sys;
    }

    template<typename T>
    T *getSystem() {
        auto it = mSystems.find(std::type_index(typeid(T)));
        if (it != mSystems.end()) {
            return dynamic_cast<T *>(it->second);
        }
        return nullptr;
    }

    template<typename T>
    std::vector<std::shared_ptr<Entity>> match() {
        std::vector<std::shared_ptr<Entity>> result;
        for (auto entity : mEntities) {
            if (entity->getComponent<T>()) {
                result.push_back(entity);
            }
        }
        return result;
    }

    template<typename T1, typename T2>
    std::vector<std::shared_ptr<Entity>> match() {
        std::vector<std::shared_ptr<Entity>> result;
        for (auto entity : mEntities) {
            if (entity->getComponent<T1>() && entity->getComponent<T2>()) {
                result.push_back(entity);
            }
        }
        return result;
    };


    template<typename T1, typename T2, typename T3>
    std::vector<std::shared_ptr<Entity>> match() {
        std::vector<std::shared_ptr<Entity>> result;
        for (auto entity : mEntities) {
            if (entity->getComponent<T1>() && entity->getComponent<T2>() && entity->getComponent<T3>()) {
                result.push_back(entity);
            }
        }
        return result;
    };


    std::shared_ptr<Entity> createEntity();
    std::shared_ptr<Entity> createEntity(std::string);
    std::shared_ptr<Entity> createEntityFromFile(std::string);
    void destroyEntity(Entity *);
    std::vector<std::shared_ptr<Entity>> all();

    void update(float);
    void updateInput();
    void updateRender(float);

    void setRender(sf::RenderTarget*);
    void render(sf::Drawable*);

    std::shared_ptr<Entity> find(int);
    std::shared_ptr<Entity> find(const char*);



	void sendMessage(std::string &message, Object *obj);
	void setRenter(Object *renter);
	void setLandlord(Object *landlord);


	//void setMediator(Mediator *mediator) {};
	//void send(std::string &message) {};
	//void onMessage(std::string &message) {};

private:
    static int mEntityIdx;
    std::vector<std::shared_ptr<Entity>> mEntities;
    std::map<std::type_index, System *> mSystems;

    sf::RenderTarget* mRender;
};

#endif //UNTITLED_WORLD_H
