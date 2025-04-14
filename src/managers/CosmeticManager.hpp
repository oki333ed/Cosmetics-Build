#pragma once

#include <Geode/Geode.hpp>

#include <matjson.hpp>
#include <types/Cosmetic.hpp>
#include <types/User.hpp>

class CosmeticManager {
public:
    static CosmeticManager* get() {
        static CosmeticManager instance;
        return &instance;
    }

    ActiveCosmetics activeCosmeticsFromJSON(matjson::Value value);

    CosmeticsUser getSelfUser() { return this->selfUser; }
    void setSelfUser(CosmeticsUser user) { this->selfUser = user; }

    void setDualCosmetics(ActiveCosmetics cosmetics, PlayerObject* p1, PlayerObject* p2);
protected:
    CosmeticsUser selfUser;
    std::vector<Cosmetic> allCosmetics;
};