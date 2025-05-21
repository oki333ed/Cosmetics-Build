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

    CCSprite* spr;
    auto regularPos = this->m_iconSprite->getScaledContentSize() + CCPoint{-3.f, 2.f};
    auto* regularHat = Build<CCSprite>::createSpriteName(fmt::format("{}.png"_spr, hat.getCosmeticID()).c_str())
        .scale(0.5f)
        .id(fmt::format("hat-{}", hat.getCosmeticID()))
        .parent(this->m_iconSprite)
        .store(spr)
        .schedule([spr, rpos = regularPos, this](float dt) {
            spr->setVisible(!this->m_isDead && !this->m_isHidden && !this->m_isDart && !this->m_isBall);  
            spr->setPosition(rpos);
        })
        .pos(regularPos)
        .collect();
}

void CosmeticsPlayerObject::drawMask(Cosmetic mask) {
    if (mask.isEmpty()) {
        return;
    }

    CCNode* spr;;
    CCNode* regularMask; 
    Build(CosmeticManager::get()->loadMask(mask.getCosmeticID(), this->m_playerColor1, this->m_playerColor2, this->m_glowColor))
        .scale(0.135f)
        .id(fmt::format("mask-{}", mask.getCosmeticID()))
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
            .id("mask_glow")
            .scale(0.135f)
            .zOrder(0);
}