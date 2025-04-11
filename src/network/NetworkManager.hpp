#pragma once

#include <Geode/Geode.hpp>

#include <any>
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXUserAgent.h>

#define API_URL "ws://127.0.0.1:8787/api/handlews"

template <typename T>
struct EventData {
    T data;
};

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
    }

    void handlePacket(int packetID, matjson::Value& packetData);

    template <class Packet>
    Packet cast(std::any value) {
       return std::any_cast<Packet>(value);
    }

    bool connected();
protected:
    ix::WebSocket webSocket;
};