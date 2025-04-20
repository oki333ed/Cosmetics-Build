#pragma once

#include <Geode/Geode.hpp>

#include <types/User.hpp>

class CosmeticSelectPopup : public geode::Popup<CosmeticsUser&> {
protected:
    bool setup(CosmeticsUser& user) override;

    int getPlayerIconIndex(IconType type);
    SimplePlayer* drawPlayer(IconType type, cocos2d::CCNode* baseNode, CosmeticsUser& user);
    void drawAllCosmetics(std::vector<Cosmetic> cosmetics);

    void drawHat(Cosmetic hat, SimplePlayer* player);
    void drawMask(Cosmetic mask, SimplePlayer* player);

public:
    static CosmeticSelectPopup* create(CosmeticsUser& user);
};