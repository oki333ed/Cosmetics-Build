#pragma once

#include <network/packets/Packet.hpp>
#include <types/Cosmetic.hpp>

class CreateUserPacket : public Packet<CreateUserPacket, 1001> {
public:
    CreateUserPacket(int accountID, std::string token) : accountID(accountID), token(token) {}

    static CreateUserPacket create(int accountID, std::string token) {
        return CreateUserPacket(accountID, token);
    }

    friend class Packet;

protected:
    matjson::Value encodeData() const {
        return matjson::makeObject({
            {"accountID", accountID},
            {"token", token}
        });
    }

    int accountID;
    std::string token;
};

class UpdateUserPacket : public Packet<UpdateUserPacket, 1002> {
public:
    UpdateUserPacket(int accountID, int creditsAmount, ActiveCosmetics activeCosmetics, AccountCosmetics accountCosmetics) : 
        accountID(accountID),
        creditsAmount(creditsAmount),
        activeCosmetics(activeCosmetics),
        accountCosmetics(accountCosmetics) {}
    
    static UpdateUserPacket create(int accountID, int creditsAmount, ActiveCosmetics activeCosmetics, AccountCosmetics accountCosmetics) {
        return UpdateUserPacket(accountID, creditsAmount, activeCosmetics, accountCosmetics);
    }

    friend class Packet;

protected:
    matjson::Value encodeData() const {
        return matjson::makeObject({
            {"accountID", accountID},
            {"creditsAmount", creditsAmount},
            {"activeCosmetics", activeCosmetics.createObject()},
            {"accountCosmetics", accountCosmetics.createObject()}
        });
    }

    int accountID;
    int creditsAmount;
    ActiveCosmetics activeCosmetics;
    AccountCosmetics accountCosmetics;
};

class RequestUserPacket : public Packet<RequestUserPacket, 1003> {
public:
    RequestUserPacket(int accountID) : accountID(accountID) {}

    static RequestUserPacket create(int accountID) {
        return RequestUserPacket(accountID);
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
