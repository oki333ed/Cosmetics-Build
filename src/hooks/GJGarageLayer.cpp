#include "GJGarageLayer.hpp"

#include <managers/CosmeticManager.hpp>
#include <UIBuilder.hpp>

using namespace geode::prelude;

bool HookedGJGarageLayer::init() {
    if (!GJGarageLayer::init()) return false;

    auto shardsMenu = static_cast<CCMenu*>(this->getChildByID("shards-menu"));

    Build<CCSprite>::createSpriteName("GJ_menuBtn_001.png")
        .scale(0.75f)
        .intoMenuItem([]() {
            CosmeticsUser user = CosmeticManager::get()->getSelfUser();
            CosmeticSelectPopup::create(user)->show();
        })
        .parent(shardsMenu);

    shardsMenu->updateLayout();

    return true;
}