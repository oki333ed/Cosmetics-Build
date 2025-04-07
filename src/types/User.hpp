#pragma once

#include "Cosmetic.hpp"

class CosmeticsUser {
public:
    CosmeticsUser() {}

    CosmeticsUser(int accountID, int creditsAmount, ActiveCosmetics activeCosmetics, AccountCosmetics accountCosmetics) : 
        accountID(accountID), creditsAmount(creditsAmount), activeCosmetics(activeCosmetics), accountCosmetics(accountCosmetics) {}

    int getAccountID() { return this->accountID; }
    int getCreditsAmount() { return this->creditsAmount; }
    ActiveCosmetics getActiveCosmetics() { return this->activeCosmetics; }
    AccountCosmetics getAccountCosmetics() { return this->accountCosmetics; }
    
    void setAccountID(int accountID) { this->accountID = accountID; }
    void setCreditsAmount(int creditsAmount) { this->creditsAmount = creditsAmount; }
    void setActiveCosmetics(ActiveCosmetics activeCosmetics) { this->activeCosmetics = activeCosmetics; }
    void setAccountCosmetics(AccountCosmetics accountCosmetics) { this->accountCosmetics = accountCosmetics; }

protected:
    int accountID;
    int creditsAmount;
    ActiveCosmetics activeCosmetics;
    AccountCosmetics accountCosmetics;
};