#pragma once

#include "network/packets/Packet.hpp"

class CreatedUserPacket : public Packet<CreatedUserPacket, 10001> {
public:
    CreatedUserPacket(matjson::Value packetData) : packetData(packetData) {}

    void handlePacket() const {
        geode::prelude::log::info("CreatedUserPacket: ", packetData["accountID"].asString().unwrap());
    }
    
protected:
    matjson::Value packetData;
};