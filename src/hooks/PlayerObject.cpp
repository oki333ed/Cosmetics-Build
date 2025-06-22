#include "PlayerObject.hpp"

#include <Geode/Geode.hpp>
#include <UIBuilder.hpp>

#include <dankmeme.globed2/include/player.hpp>
#include <managers/CosmeticManager.hpp>
#include <network/NetworkManager.hpp>
#include <network/packets/Client.hpp>

using namespace geode::prelude;

void CosmeticsPlayerObject::resetObject()  {
    PlayerObject::resetObject();

    this->setCosmetics(m_fields->m_activeCosmetics);
}

void CosmeticsPlayerObject::setCosmetics(ActiveCosmetics cosmetics) {
    m_fields->m_activeCosmetics = cosmetics;
    this->drawHat(cosmetics.getHat());
    this->drawMask(cosmetics.getMask());
}

void CosmeticsPlayerObject::drawHat(Cosmetic hat) {
    if (hat.isEmpty()) {
        return;
    }

    CCNode* spr;
    CCNode* regularHat;
    Build(CosmeticManager::get()->loadHat(hat.getCosmeticID(), this->m_playerColor1, this->m_playerColor2, this->m_glowColor))
        .scale(0.75f)
        .id(fmt::format("hat-{}"_spr, hat.getCosmeticID()))
        .parent(this->m_mainLayer)
        .anchorPoint({0.5f, 0.5f})
        .zOrder(1)
        .store(spr)
        .schedule([spr, this](float dt) {
            spr->setVisible(!this->m_isDead && !this->m_isHidden && !this->m_isDart && !this->m_isBall);  
        })
        .store(regularHat)
        .intoNewSibling(CCSprite::createWithSpriteFrameName(fmt::format("{}_outline.png"_spr, hat.getCosmeticID()).c_str()))
            .color(this->m_glowColor)
            .id("hat_glow")
            .scale(0.75f)
            .zOrder(0);
}

void CosmeticsPlayerObject::drawMask(Cosmetic mask) {
    if (mask.isEmpty()) {
        return;
    }

    CCNode* spr;
    CCNode* regularMask; 
    Build(CosmeticManager::get()->loadMask(mask.getCosmeticID(), this->m_playerColor1, this->m_playerColor2, this->m_glowColor))
        .scale(0.75f)
        .id(fmt::format("mask-{}"_spr, mask.getCosmeticID()))
        .parent(this->m_mainLayer)
        .anchorPoint({0.5f, 0.5f})
        .zOrder(1)
        .store(spr)
        .schedule([spr, this](float dt) {
            spr->setVisible(!this->m_isDead && !this->m_isHidden && !this->m_isDart && !this->m_isBall);  
        })
        .store(regularMask)
        .intoNewSibling(CCSprite::createWithSpriteFrameName(fmt::format("{}_outline.png"_spr, mask.getCosmeticID()).c_str()))
            .color(this->m_glowColor)
            .id("mask_glow"_spr)
            .scale(0.75f)
            .zOrder(0);
}