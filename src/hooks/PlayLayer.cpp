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
        //log::info("left account id: {}", accountID);
    });

    if (onPlayerLeave) {
        onPlayerLeave.unwrap();
    } else {
        log::info("onPlayerLeave Error: {}", onPlayerLeave.unwrapErr());
    }

    return true;
}

void HookedPlayLayer::levelComplete() {
    float creditsPercentage = 1.f;
    if (this->m_level->m_normalPercent == 100) {
        creditsPercentage = 0.25f;
    }

    GJDifficulty difficulty = this->m_level->m_difficulty;
    CosmeticManager* cm = CosmeticManager::get();
    CosmeticsUser currentUser = cm->getSelfUser();
    int creditsAmount = 0;
    switch (difficulty) {
        case GJDifficulty::NA:
        case GJDifficulty::Auto: {
            break;
        }
        case GJDifficulty::Easy: {
            creditsPercentage = 0.f;
            creditsAmount = 15;
            break;
        }
        case GJDifficulty::Normal: {
            creditsPercentage = 0.f;
            creditsAmount = 20;
            break;
        }
        case GJDifficulty::Hard: {
            creditsPercentage = 0.f;
            creditsAmount = 25;
            break;
        }
        case GJDifficulty::Harder: {
            creditsPercentage = 0.f;
            creditsAmount = 30;
            break;
        }
        case GJDifficulty::Insane: {
            creditsPercentage = 0.f;
            creditsAmount = 50;
            break;
        }
        case GJDifficulty::DemonEasy: {
            creditsAmount = 100;
            break;
        }
        case GJDifficulty::DemonMedium: {
            creditsAmount = 250;
            break;
        }
        case GJDifficulty::Demon: {
            creditsAmount = 400;
            break;
        }
        case GJDifficulty::DemonInsane: {
            creditsAmount = 650;
            break;
        }
        case GJDifficulty::DemonExtreme: {
            creditsAmount = 1000;
            break;
        }
    }

    creditsAmount = creditsAmount * creditsPercentage;

    cm->updateSelfUser(
        CosmeticsUser(
            currentUser.getAccountID(), creditsAmount, currentUser.getActiveCosmetics(), currentUser.getAccountCosmetics()
        )
    );

    PlayLayer::levelComplete();
}