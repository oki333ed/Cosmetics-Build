#pragma once

#include <any>
#include <map>

#include "Server/Account.hpp"

std::map<int, std::any> serverPackets = {
    {10001, CreatedUserPacket()},
    {10003, UserDataPacket()}
};