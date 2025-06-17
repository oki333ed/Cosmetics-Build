#include "CosmeticManager.hpp"
#include "hooks/PlayerObject.hpp"

#include <UIBuilder.hpp>

using namespace geode::prelude;

ActiveCosmetics CosmeticManager::activeCosmeticsFromJSON(matjson::Value value) {
    return ActiveCosmetics(
        (!value["hat"].isNull()) ? Cosmetic(value["hat"]) : Cosmetic(),
        (!value["mask"].isNull()) ? Cosmetic(value["mask"]) : Cosmetic(),
        (!value["object"].isNull()) ? Cosmetic(value["object"]) : Cosmetic(),
        (!value["particle"].isNull()) ? Cosmetic(value["particle"]) : Cosmetic()
    );
}

void CosmeticManager::setDualCosmetics(ActiveCosmetics cosmetics, PlayerObject* p1, PlayerObject* p2) {
    static_cast<CosmeticsPlayerObject*>(p1)->setCosmetics(cosmetics);
    static_cast<CosmeticsPlayerObject*>(p2)->setCosmetics(cosmetics);
}

CCNode* CosmeticManager::loadHat(int id, ccColor3B primaryColor, ccColor3B secondaryColor, ccColor3B glowColor) {
    CCNode* node;
    Build<CCNode>::create()
    .store(node)
    .intoNewChild(CCSprite::createWithSpriteFrameName(fmt::format("{}_first.png"_spr, id).c_str()))
        .color(primaryColor)
        .id("mask_first")
    .intoNewSibling(CCSprite::createWithSpriteFrameName(fmt::format("{}_second.png"_spr, id).c_str()))
        .color(secondaryColor)
        .id("mask_second");
    
    if (auto white = CCSprite::createWithSpriteFrameName(fmt::format("{}_white.png"_spr, id).c_str())) {
        white->setID("mask_white");
        node->addChild(white);
    }

    return node;
}

CCNode* CosmeticManager::loadMask(int id, ccColor3B primaryColor, ccColor3B secondaryColor, ccColor3B glowColor) {
    CCNode* node;
    Build<CCNode>::create()
        .store(node)
        .intoNewChild(CCSprite::createWithSpriteFrameName(fmt::format("{}_first.png"_spr, id).c_str()))
            .color(primaryColor)
            .id("mask_first")
        .intoNewSibling(CCSprite::createWithSpriteFrameName(fmt::format("{}_second.png"_spr, id).c_str()))
            .color(secondaryColor)
            .id("mask_second");
    
    return node;
}