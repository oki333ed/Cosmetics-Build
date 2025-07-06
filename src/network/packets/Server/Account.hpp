#pragma once

#include "network/packets/Packet.hpp"

#include <managers/CosmeticManager.hpp>
#include <network/NetworkManager.hpp>
#include <network/packets/Client.hpp>

class CreatedUserPacket : public Packet<CreatedUserPacket, 10001> {
public:
    CreatedUserPacket() {}

    void handlePacket(matjson::Value& packetData) {
        bool isSuccess = packetData["code"] == 200;
        if (!isSuccess) {
            NetworkManager::get()->send(RequestUserPacket::create(GJAccountManager::get()->m_accountID));
            return;
        }
        
        geode::Loader::get()->queueInMainThread([packetData, isSuccess] {
            geode::Notification::create(
                fmt::format("[Cosmetics]: {}", packetData["message"].asString().unwrap()), 
                geode::NotificationIcon::Success, 0.5f)->show();
    
        });
    }
};

class UserDataPacket : public Packet<UserDataPacket, 10002> {
public:
    UserDataPacket() {}

    void handlePacket(matjson::Value& packetData) {
        CosmeticsUser user = CosmeticsUser();
        user.setAccountID(packetData["accountID"].asInt().unwrap());
        user.setCreditsAmount(packetData["creditsAmount"].asInt().unwrap());

        auto hat = (!packetData["activeCosmetics"]["hat"].isNull()) ? new Cosmetic(
            packetData["activeCosmetics"]["hat"]
        ) : new Cosmetic();
        auto mask = (!packetData["activeCosmetics"]["mask"].isNull()) ? new Cosmetic(
            packetData["activeCosmetics"]["mask"]
        ) : new Cosmetic();
        auto object = (!packetData["activeCosmetics"]["object"].isNull()) ? new Cosmetic(
            packetData["activeCosmetics"]["object"]
        ) : new Cosmetic();
        auto particle = (!packetData["activeCosmetics"]["particle"].isNull()) ? new Cosmetic(
            packetData["activeCosmetics"]["particle"]
        ) : new Cosmetic();
        
        user.setActiveCosmetics(ActiveCosmetics(
            *hat, 
            *mask, 
            *object, 
            *particle
        ));

        std::vector<Cosmetic> hats, masks, objects, particles;
        for (auto hat : packetData["allCosmetics"]["hats"].asArray().unwrap()) {
            hats.push_back(Cosmetic(hat));
        }

        for (auto mask : packetData["allCosmetics"]["masks"].asArray().unwrap()) {
            masks.push_back(Cosmetic(mask));
        }

        for (auto object : packetData["allCosmetics"]["objects"].asArray().unwrap()) {
            objects.push_back(Cosmetic(object));
        }

        for (auto particle : packetData["allCosmetics"]["particles"].asArray().unwrap()) {
            particles.push_back(Cosmetic(particle));
        }

        user.setAccountCosmetics(AccountCosmetics(
            hats, masks, objects, particles
        ));

        CosmeticManager::get()->setSelfUser(user);
        geode::log::info("new credits amount: {}", user.getCreditsAmount());
    }
};