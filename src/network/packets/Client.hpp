#pragma once

#include "Packet.hpp"

class AddCosmeticPacket : public Packet<AddCosmeticPacket, 1001> {
public:
    AddCosmeticPacket(int cosmeticID, bool isActive) : 
        cosmeticID(cosmeticID), 
        isActive(isActive) {}
    
    static AddCosmeticPacket* create(int cosmeticID, bool isActive) {
        return new AddCosmeticPacket(cosmeticID, isActive);
    }
    
    friend class Packet;

protected:
    matjson::Value encodeData() const {
        return matjson::makeObject({
            {"cosmeticID", cosmeticID},
            {"isActive", isActive}
        });
    }

    int cosmeticID;
    bool isActive;
};