#pragma once

#include <Geode/Geode.hpp>

#include <managers/CosmeticManager.hpp>
#include <types/Cosmetic.hpp>

#include <UIBuilder.hpp>

class CosmeticsSimplePlayer : public SimplePlayer {
protected:
    Cosmetic hat;
    Cosmetic mask;

public:
    void drawHat(Cosmetic hat, cocos2d::ccColor3B playerColor1, cocos2d::ccColor3B playerColor2, cocos2d::ccColor3B playerGlowColor) {
        auto cm = CosmeticManager::get();

        auto existingHat = this->getChildByID(fmt::format("hat-{}"_spr, this->hat.getCosmeticID()));
        auto existingHatGlow = this->getChildByID(fmt::format("hat-{}-glow"_spr, this->hat.getCosmeticID()));

        if (existingHat && existingHatGlow) {
            existingHat->removeMeAndCleanup();
            existingHatGlow->removeMeAndCleanup();
        }

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

        this->hat = hat;
    }

    void drawMask(Cosmetic mask, cocos2d::ccColor3B playerColor1, cocos2d::ccColor3B playerColor2, cocos2d::ccColor3B playerGlowColor) {
        auto cm = CosmeticManager::get();

        auto existingMask = this->getChildByID(fmt::format("mask-{}"_spr, this->mask.getCosmeticID()));
        auto existingMaskGlow = this->getChildByID(fmt::format("mask-{}-glow"_spr, this->mask.getCosmeticID()));

        if (existingMask && existingMaskGlow) {
            existingMask->removeMeAndCleanup();
            existingMaskGlow->removeMeAndCleanup();
        }

        Build(cm->loadMask(mask.getCosmeticID(), playerColor1, playerColor2, playerGlowColor))
            .scale(0.75f)
            .id(fmt::format("mask-{}"_spr, mask.getCosmeticID()))
            .parent(this)
            .anchorPoint({0.5f, 0.5f})
            .zOrder(1)
            .intoNewSibling(CCSprite::createWithSpriteFrameName(fmt::format("{}_outline.png"_spr, mask.getCosmeticID()).c_str()))
                .color(this->m_glowColor)
                .id(fmt::format("mask-{}-glow"_spr, mask.getCosmeticID()))
                .scale(0.75f)
                .zOrder(0);

        this->mask = mask;
    }

    void drawCosmetics(ActiveCosmetics cosmetics, cocos2d::ccColor3B playerColor1, cocos2d::ccColor3B playerColor2, cocos2d::ccColor3B playerGlowColor) {
        auto cm = CosmeticManager::get();
        auto hat = cosmetics.getHat();
        auto mask = cosmetics.getMask();

        if (!hat.isEmpty()) {
            this->drawHat(hat, playerColor1, playerColor2, playerGlowColor);
        }

        if (!mask.isEmpty()) {
            this->drawMask(mask, playerColor1, playerColor2, playerGlowColor);
        }
    }
};