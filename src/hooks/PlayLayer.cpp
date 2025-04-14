#include "PlayLayer.hpp"

#include <dankmeme.globed2/include/callbacks.hpp>
#include <dankmeme.globed2/include/player.hpp>
#include <events/EventDispatcher.hpp>
#include <Geode/Geode.hpp>
#include <hooks/PlayerObject.hpp>
#include <managers/CosmeticManager.hpp>
#include <network/NetworkManager.hpp>
#include <network/packets/Client.hpp>

using namespace geode::prelude;

bool HookedPlayLayer::init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
    if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;

    auto gjbgl = GJBaseGameLayer::get();
    auto cm = CosmeticManager::get();

    auto selfCosmetics = cm->getSelfUser().getActiveCosmetics();
    cm->setDualCosmetics(selfCosmetics, gjbgl->m_player1, gjbgl->m_player2);

    auto onPlayerJoin = globed::callbacks::onPlayerJoin([cm](int accountID, PlayerObject* p1, PlayerObject* p2) {
        auto cosmeticsPacket = RequestUserCosmeticsPacket::create(accountID);
        NetworkManager::get()->send(cosmeticsPacket);

        Cosmetics::EventDispatcher::get()->registerListener(new Cosmetics::Event<ActiveCosmetics>("UserCosmeticsPacket", [cm, p1, p2](ActiveCosmetics activeCosmetics) {
            cm->setDualCosmetics(activeCosmetics, p1, p2);
        }));
    });

    if (onPlayerJoin) {
        onPlayerJoin.unwrap();
    } else {
        log::info("onPlayerJoin Error: {}", onPlayerJoin.unwrapErr());
    }

    auto onPlayerLeave = globed::callbacks::onPlayerLeave([](int accountID, PlayerObject* p1, PlayerObject* p2) {
        log::info("left account id: {}", accountID);
    });

    if (onPlayerLeave) {
        onPlayerLeave.unwrap();
    } else {
        log::info("onPlayerLeave Error: {}", onPlayerLeave.unwrapErr());
    }

    return true;
}