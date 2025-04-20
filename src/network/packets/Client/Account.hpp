#pragma once

#include "network/packets/Packet.hpp"

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
    UpdateUserPacket(int accountID, int creditsAmount) : 
        accountID(accountID),
        creditsAmount(creditsAmount) {}
    
    static UpdateUserPacket create(int accountID, int creditsAmount) {
        return UpdateUserPacket(accountID, creditsAmount);
    }

    friend class Packet;

protected:
    matjson::Value encodeData() const {
        return matjson::makeObject({
            {"accountID", accountID},
            {"creditsAmount", creditsAmount}
        });
    }

    int accountID;
    int creditsAmount;
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
