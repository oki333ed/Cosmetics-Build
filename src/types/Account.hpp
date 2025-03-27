#pragma once

#include <matjson.hpp>

class Account {
public:
    Account(int accountID, int creditsAmount) {
        this->accountID = accountID;
        this->creditsAmount = creditsAmount;
    }

    Account(matjson::Value value) {
        this->accountID = value["accountID"].asInt().unwrap();
        this->creditsAmount = value["creditsAmount"].asInt().unwrap();
    }

    int getAccountID() {return this->accountID;}
    int getCreditsAmount() {return this->creditsAmount;}

    void setAccountID(int accID) {this->accountID = accID;}
    void setCreditsAmount(int cred) {this->creditsAmount = cred;}

protected:
    int accountID;
    int creditsAmount;
};