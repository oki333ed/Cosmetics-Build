#pragma once

#include <managers/CosmeticManager.hpp>
#include "network/packets/Packet.hpp"

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
        
    }
};