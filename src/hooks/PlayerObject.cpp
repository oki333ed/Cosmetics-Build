#include "PlayerObject.hpp"

#include <Geode/Geode.hpp>
#include <UIBuilder.hpp>

#include <managers/CosmeticManager.hpp>

using namespace geode::prelude;

bool CosmeticsPlayerObject::init(int p0, int p1, GJBaseGameLayer* p2, cocos2d::CCLayer* p3, bool p4) {
    if (!PlayerObject::init(p0, p1, p2, p3, p4)) return false;


    if (!CosmeticManager::get()->getSelfUser().isEmpty())
        this->setCosmetics(CosmeticManager::get()->getSelfUser().getActiveCosmetics());

    return true;
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
    auto regularPos = this->m_iconSprite->getScaledContentSize();
    auto* regularMask = Build<CCSprite>::createSpriteName(fmt::format("{}.png"_spr, mask.getCosmeticID()).c_str())
        .scale(0.5f)
        .id(fmt::format("hat-{}", mask.getCosmeticID()))
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