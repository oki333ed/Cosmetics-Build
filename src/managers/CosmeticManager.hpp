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

protected:
    CosmeticsUser selfUser;
};