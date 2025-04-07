#pragma once

#include "network/packets/Packet.hpp"

#include "managers/CosmeticManager.hpp"

class CreatedUserPacket : public Packet<CreatedUserPacket, 10001> {
public:
    CreatedUserPacket() {}

    void handlePacket(matjson::Value& packetData) {
        bool isSuccess = packetData["code"] == 200;
        geode::Loader::get()->queueInMainThread([packetData, isSuccess] {
            geode::Notification::create(
                fmt::format("[Cosmetics]: {}", packetData["message"].asString().unwrap()), 
                (isSuccess) ? geode::NotificationIcon::Success : geode::NotificationIcon::Error, 0.5f)->show();
    
        });
    }
};

class UserDataPacket : public Packet<CreatedUserPacket, 10003> {
public:
    UserDataPacket() {}

    void handlePacket(matjson::Value& packetData) {
        geode::log::info("packetData: {}", packetData.dump());
        CosmeticsUser user = CosmeticsUser();
        user.setAccountID(packetData["accountID"].asInt().unwrap());
        user.setCreditsAmount(packetData["creditsAmount"].asInt().unwrap());

        auto hat = (packetData["activeCosmetics"]["hat"].isNull()) ? new Cosmetic(
            packetData["activeCosmetics"]["hat"]
        ) : nullptr;
        auto mask = (packetData["activeCosmetics"]["mask"].isNull()) ? new Cosmetic(
            packetData["activeCosmetics"]["mask"]
        ) : nullptr;
        auto object = (packetData["activeCosmetics"]["object"].isNull()) ? new Cosmetic(
            packetData["activeCosmetics"]["object"]
        ) : nullptr;
        auto particle = (packetData["activeCosmetics"]["particle"].isNull()) ? new Cosmetic(
            packetData["activeCosmetics"]["particle"]
        ) : nullptr;

        user.setActiveCosmetics(ActiveCosmetics(
            *hat, *mask, *object, *particle
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
    }
};