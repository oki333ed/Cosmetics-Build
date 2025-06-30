#pragma once

#include <events/EventDispatcher.hpp>
#include <managers/CosmeticManager.hpp>
#include <network/packets/Packet.hpp>

class CosmeticAddedPacket : public Packet<CosmeticAddedPacket, 12001> {
public:
    CosmeticAddedPacket() {}

    void handlePacket(matjson::Value& packetData) {

    }
};

class CosmeticSetActivePacket : public Packet<CosmeticSetActivePacket, 12002> {
public:
    CosmeticSetActivePacket() {}

    void handlePacket(matjson::Value& packetData) {

    }
};

class UserCosmeticsPacket : public Packet<UserCosmeticsPacket, 12003> {
public:
    UserCosmeticsPacket() {}

    void handlePacket(matjson::Value& packetData) {
        auto activeCosmetics = CosmeticManager::get()->activeCosmeticsFromJSON(packetData);
        Cosmetics::EventDispatcher::get()->dispatch("UserCosmeticsPacket", activeCosmetics);
    }
};

class AllCosmeticsPacket : public Packet<AllCosmeticsPacket, 12004> {
public:
    AllCosmeticsPacket() {}

    void handlePacket(matjson::Value& packetData) {
        std::vector<FullCosmetic> cosmetics;
        for (auto cosmetic : packetData.asArray().unwrap()) {
            cosmetics.push_back(FullCosmetic(cosmetic));
        }

        Cosmetics::EventDispatcher::get()->dispatch("AllCosmeticsPacket", cosmetics);
    }
};