#pragma once

#include <functional>

#include <types/Account.hpp>
#include <types/Cosmetic.hpp>

#define API_URL "http://127.0.0.1:8787"

class APIManager {
public:
    static APIManager* get() {
        static APIManager instance;
        return &instance;
    }

    void addCosmeticToUser(int accountID, int cosmeticID, bool isActive, std::function<void()> func);
    void createUser(int accountID, std::function<void()> func);
    void getAccount(int accountID, std::function<void(Account*)> func);
    void getAllCosmetics(std::function<void(std::vector<Cosmetic*>)> func);
    void setCosmeticActive(int accountID, int cosmeticID, std::function<void()> func);
};