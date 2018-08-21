//
// Created by Jie on 2018/8/7.
//


#include "World.h"
#include "Sprite.h"
#include "Transform.h"
#include "RenderSystem.h"

#include <SFML/Graphics.hpp>

RenderSystem::RenderSystem() {
    console = spdlog::stdout_color_mt("Render System");
}

void RenderSystem::updateRender(float dt) {
    auto list = mWorld->match<Transform, Sprite>();
    // mLogger->info("need update entities count : {}", list.size());
    for (auto entity: list) {
        auto sprite = entity->getComponent<Sprite>();
        auto transform = entity->getComponent<Transform>();

        sprite->sprite.setPosition(transform->position.x, transform->position.y);
        sprite->sprite.setScale(transform->scale.x, transform->scale.y);
        sprite->sprite.setRotation(transform->angle);

        if(sprite->hasAnimations)
            sprite->next(dt);

        mWorld->render(&(sprite->sprite));
    }

    // console->info(list.size());
}