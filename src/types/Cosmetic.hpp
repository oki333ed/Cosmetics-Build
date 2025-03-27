#pragma once

#include <matjson.hpp>

class Cosmetic {
public:
    Cosmetic(int cosmeticID, std::string cosmeticName, int cosmeticAmount) {
        this->cosmeticID = cosmeticID;
        this->cosmeticName = cosmeticName;
        this->cosmeticAmount = cosmeticAmount;
    }

    Cosmetic(matjson::Value value) {
        this->cosmeticID = value["cosmeticID"].asInt().unwrap();
        this->cosmeticName = value["cosmeticName"].asString().unwrap();
        this->cosmeticAmount = value["cosmeticAmount"].asInt().unwrap();
    }

    int getCosmeticID() {return this->cosmeticID;}
    std::string getCosmeticName() {return this->cosmeticName;}
    int getCosmeticAmount() {return this->cosmeticAmount;}

    void setCosmeticID(int cosID) {this->cosmeticID = cosID;}
    void setCosmeticName(std::string name) {this->cosmeticName = name;}
    void setCosmeticAmount(int amount) {this->cosmeticAmount = amount;}
protected:
    int cosmeticID;
    std::string cosmeticName;
    int cosmeticAmount;
};