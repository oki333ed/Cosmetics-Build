#pragma once

#include <Geode/modify/PlayerObject.hpp>

#include <defs.hpp>
#include <types/Cosmetic.hpp>

struct CosmeticsPlayerObject : geode::Modify<CosmeticsPlayerObject, PlayerObject> {
    struct Fields {
        ActiveCosmetics m_activeCosmetics;
    };

    void setCosmetics(ActiveCosmetics cosmetics);
    void drawHat(Cosmetic hat);
    void drawMask(Cosmetic mask);
};