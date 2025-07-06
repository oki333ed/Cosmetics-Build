#pragma once

#include <Geode/Geode.hpp>

#include <managers/CosmeticManager.hpp>
#include <types/Cosmetic.hpp>

#include <UIBuilder.hpp>

class CosmeticsSimplePlayer : public SimplePlayer {
public:
    void drawCosmetics(ActiveCosmetics cosmetics, cocos2d::ccColor3B playerColor1, cocos2d::ccColor3B playerColor2, cocos2d::ccColor3B playerGlowColor) {
        auto cm = CosmeticManager::get();

        auto hat = cosmetics.getHat();
        auto mask = cosmetics.getMask();

        if (!hat.isEmpty()) {
            Build(cm->loadHat(hat.getCosmeticID(), playerColor1, playerColor2, playerGlowColor))
                .posY(23.f)
                .id(fmt::format("hat-{}"_spr, hat.getCosmeticID()))
                .parent(this)
                .anchorPoint({0.5f, 0.5f})
                .zOrder(1)
                .intoNewSibling( cocos2d::CCSprite::createWithSpriteFrameName(fmt::format("{}_outline.png"_spr, hat.getCosmeticID()).c_str()))
                    .color(playerGlowColor)
                    .id(fmt::format("hat-{}-glow"_spr, hat.getCosmeticID()))
                    .posY(23.f)
                    .zOrder(0);
        }
    }
};