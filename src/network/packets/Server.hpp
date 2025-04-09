#pragma once

#include <any>
#include <map>

#include "Server/Account.hpp"
#include "Server/Cosmetic.hpp"

std::map<int, std::any> serverPackets = {
    {10001, CreatedUserPacket()},
    {10002, UserDataPacket()},
    {12001, CosmeticAddedPacket()},
    {12002, CosmeticSetActivePacket()},
    {12003, UserCosmeticsPacket()}
    
};