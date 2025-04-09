#pragma once

#include "network/packets/Packet.hpp"

class AddCosmeticPacket : public Packet<AddCosmeticPacket, 2001> {
public:
    AddCosmeticPacket(int accountID, int cosmeticID, bool isActive) : 
        accountID(accountID),
        cosmeticID(cosmeticID), 
        isActive(isActive) {}
    
    static AddCosmeticPacket create(int accountID, int cosmeticID, bool isActive) {
        return AddCosmeticPacket(accountID, cosmeticID, isActive);
    }
    
    friend class Packet;

protected:
    matjson::Value encodeData() const {
        return matjson::makeObject({
            {"accountID", accountID},
            {"cosmeticID", cosmeticID},
            {"isActive", isActive}
        });
    }

    int accountID;
    int cosmeticID;
    bool isActive;
};

class SetCosmeticActivePacket : public Packet<SetCosmeticActivePacket, 2002> {
public:
    SetCosmeticActivePacket(int accountID, int cosmeticID) : 
        accountID(accountID),
        cosmeticID(cosmeticID) {}

    static SetCosmeticActivePacket create(int accountID, int cosmeticID) {
        return SetCosmeticActivePacket(accountID, cosmeticID);
    }

    friend class Packet;

protected:
    matjson::Value encodeData() const {
        return matjson::makeObject({
            {"accountID", accountID},
            {"cosmeticID", cosmeticID}
        });
    }

    int accountID;
    int cosmeticID;
};

class RequestUserCosmeticsPacket : public Packet<RequestUserCosmeticsPacket, 2003> {
public:
    RequestUserCosmeticsPacket(int accountID) : accountID(accountID) {}

    static RequestUserCosmeticsPacket create(int accountID) {
        return RequestUserCosmeticsPacket(accountID);
    }

    friend class Packet;

protected:
    matjson::Value encodeData() const {
        return matjson::makeObject({
            {"accountID", accountID}
        });
    }

    int accountID;
};