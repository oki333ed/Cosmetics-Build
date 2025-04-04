#include "NetworkManager.hpp"

#include "packets/Server.hpp"

using namespace geode::prelude;

void NetworkManager::init() {
    ix::initNetSystem();
    this->webSocket.setUrl(API_URL);
    this->webSocket.setPingInterval(45);
    this->webSocket.setOnMessageCallback([this](const ix::WebSocketMessagePtr& msg) {
        switch (msg->type) {
            case ix::WebSocketMessageType::Open: {
                log::info("Connection established with server");
                break;
            }
            case ix::WebSocketMessageType::Message: {
                matjson::Value parsedMsg = matjson::parse(msg->str).unwrapOr(nullptr);
                if (parsedMsg != nullptr) {
                    this->handlePacket(parsedMsg["packetID"].asInt().unwrap(), parsedMsg["data"].object());
                }
                break;
            }
            case ix::WebSocketMessageType::Error: {
                log::error("Error connecting to server: {}", msg->errorInfo.reason);
                break;
            }
        }
    });
    this->webSocket.start();
}

void NetworkManager::handlePacket(int packetID, matjson::Value packetData) {
    switch (packetID) {
        case 10001: {
            this->handle(CreatedUserPacket(packetData));
            break;
        }
    }
}