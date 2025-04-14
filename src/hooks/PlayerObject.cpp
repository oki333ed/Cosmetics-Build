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
        .schedule([spr, rpos = regularPos](float dt) {
            auto obj = typeinfo_cast<PlayerObject*>(spr->getParent()->getParent()->getParent());
            spr->setVisible(obj && !obj->m_isDead && !obj->m_isHidden && !obj->m_isDart && !obj->m_isBall);

            if (obj) {
                if (!obj->m_isSwing) {
                    spr->setPosition(rpos);
                } else {
                    spr->setPosition(rpos + CCPoint{5.f, 6.f});
                }
            }
        })
        .pos(regularPos)
        .collect();
}

void CosmeticsPlayerObject::drawMask(Cosmetic mask) {
    if (mask.isEmpty()) {
        return;
    }

    CCSprite* spr;
    auto regularPos = this->m_iconSprite->getScaledContentSize() + CCPoint{6.5f, 6.5f};
    auto* regularMask = Build<CCSprite>::createSpriteName(fmt::format("{}.png"_spr, mask.getCosmeticID()).c_str())
        .scale(0.5f)
        .id(fmt::format("mask-{}", mask.getCosmeticID()))
        .parent(this->m_iconSprite)
        .store(spr)
        .schedule([spr, rpos = regularPos](float dt) {
            auto obj = typeinfo_cast<PlayerObject*>(spr->getParent()->getParent()->getParent());
            spr->setVisible(obj && !obj->m_isDead && !obj->m_isHidden && !obj->m_isDart && !obj->m_isBall);

            if (obj) {
                if (!obj->m_isSwing) {
                    spr->setPosition(rpos);
                } else {
                    spr->setPosition(rpos + CCPoint{5.f, 6.f});
                }
            }
        })
        .pos(regularPos)
        .collect();
}