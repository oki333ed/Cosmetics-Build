#include "CosmeticManager.hpp"

#include <hooks/PlayerObject.hpp>
#include <network/NetworkManager.hpp>
#include <network/packets/Client.hpp>

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

void CosmeticManager::updateSelfUser(CosmeticsUser user) {
    auto nm = NetworkManager::get();

    nm->send(
        UpdateUserPacket::create(
            user.getAccountID(), user.getCreditsAmount(), user.getActiveCosmetics(), user.getAccountCosmetics()
        )
    );
}

void CosmeticManager::updateActiveCosmetics(CosmeticsUser user) {
    for (auto cosmetic : user.getActiveCosmetics().getAllCosmetics()) {
        NetworkManager::get()->send(
            SetCosmeticActivePacket::create(user.getAccountID(), cosmetic.getCosmeticID())
        );
    }
}

void CosmeticManager::setDualCosmetics(ActiveCosmetics cosmetics, PlayerObject* p1, PlayerObject* p2) {
    static_cast<CosmeticsPlayerObject*>(p1)->setCosmetics(cosmetics);
    static_cast<CosmeticsPlayerObject*>(p2)->setCosmetics(cosmetics);
}

CCNode* CosmeticManager::loadHat(int id, ccColor3B primaryColor, ccColor3B secondaryColor, ccColor3B glowColor) {
    CCNode* node = CCNode::create();

    auto first = CCSprite::createWithSpriteFrameName(fmt::format("{}_first.png"_spr, id).c_str());
    if (first && !first->getUserObject("geode.texture-loader/fallback")) {
        first->setColor(primaryColor);
        first->setID("mask_first");
        node->addChild(first);
    }

    auto second = CCSprite::createWithSpriteFrameName(fmt::format("{}_second.png"_spr, id).c_str());
    if (second && !second->getUserObject("geode.texture-loader/fallback")) {
        second->setColor(secondaryColor);
        second->setID("mask_second");
        node->addChild(second);
    }

    auto white = CCSprite::createWithSpriteFrameName(fmt::format("{}_white.png"_spr, id).c_str());
    if (white && !white->getUserObject("geode.texture-loader/fallback")) {
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
            .id("mask_second"_spr);
    
    return node;
}