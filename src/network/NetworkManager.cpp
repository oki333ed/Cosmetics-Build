#include "NetworkManager.hpp"

#include "packets/Server.hpp"

#include <Geode/utils/web.hpp>

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
                    this->handlePacket(parsedMsg["packetID"].asInt().unwrap(), parsedMsg["data"]);
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

void NetworkManager::handlePacket(int packetID, matjson::Value& packetData) {
    std::any packet = serverPackets[packetID];
    switch (packetID) {
        case 10001: {
            this->cast<CreatedUserPacket>(packet).handlePacket(packetData);
            break;
        }
        
        case 10002: {
            this->cast<UserDataPacket>(packet).handlePacket(packetData);
            break;
        }

        case 12001: {
            this->cast<CosmeticAddedPacket>(packet).handlePacket(packetData);
            break;
        }

        case 12002: {
            this->cast<CosmeticSetActivePacket>(packet).handlePacket(packetData);
            break;
        }

        case 12003: {
            this->cast<UserCosmeticsPacket>(packet).handlePacket(packetData);
            break;
        }

        case 12004: {
            this->cast<AllCosmeticsPacket>(packet).handlePacket(packetData);
        }
    }
}

bool NetworkManager::connected() {
    if (this->webSocket.getReadyState() == ix::ReadyState::Open) {
        return true;
    }

    return false;
}