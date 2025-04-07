#pragma once

#include <Geode/Geode.hpp>

#include "types/User.hpp"

class CosmeticManager {
public:
    static CosmeticManager* get() {
        static CosmeticManager instance;
        return &instance;
    }

    CosmeticsUser getSelfUser() { return this->selfUser; }

    void setSelfUser(CosmeticsUser user) { this->selfUser = user; }

protected:
    CosmeticsUser selfUser;
};