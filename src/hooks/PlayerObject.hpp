#pragma once

#include <Geode/modify/PlayerObject.hpp>

#include <defs.hpp>
#include <types/Cosmetic.hpp>

struct CosmeticsPlayerObject : geode::Modify<CosmeticsPlayerObject, PlayerObject> {
    struct Fields {
        ActiveCosmetics m_activeCosmetics;
    };

    $override
    bool init(int p0, int p1, GJBaseGameLayer* p2, cocos2d::CCLayer* p3, bool p4);

    void setCosmetics(ActiveCosmetics cosmetics);
    void drawHat(Cosmetic hat);
    void drawMask(Cosmetic mask);
};