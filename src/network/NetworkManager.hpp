#pragma once

#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXUserAgent.h>

class NetworkManager {
public:
    static NetworkManager* get() {
        static NetworkManager instance;
        return &instance;
    }

    void init();

    
};