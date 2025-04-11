#include "PlayLayer.hpp"

#include <dankmeme.globed2/include/callbacks.hpp>
#include <dankmeme.globed2/include/player.hpp>
#include <Geode/Geode.hpp>
#include <hooks/PlayerObject.hpp>
#include <network/NetworkManager.hpp>
#include <network/packets/Client.hpp>

using namespace geode::prelude;

bool HookedPlayLayer::init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
    if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;

    auto onPlayerJoin = globed::callbacks::onPlayerJoin([](int accountID, PlayerObject* p1, PlayerObject* p2) {
        auto cosmeticsPacket = RequestUserCosmeticsPacket::create(accountID);
        NetworkManager::get()->send(cosmeticsPacket);

        
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