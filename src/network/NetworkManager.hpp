#pragma once

#include <Geode/Geode.hpp>

#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXUserAgent.h>

#define API_URL "ws://127.0.0.1:8787/api/handlews"

class NetworkManager {
public:
    ~NetworkManager() {
        this->webSocket.stop();
        ix::uninitNetSystem();
    }

    static NetworkManager* get() {
        static NetworkManager instance;
        return &instance;
    }

    void init();

    template <typename Packet>
    void send(Packet const& packet) {
        std::string val = packet.encode().dump();
        auto res = this->webSocket.sendText(val);
        geode::prelude::log::info("success?: {}", res.success);
    }

protected:
    ix::WebSocket webSocket;
};