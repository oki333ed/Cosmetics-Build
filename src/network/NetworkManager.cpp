#include "NetworkManager.hpp"

using namespace geode::prelude;

void NetworkManager::init() {
    ix::initNetSystem();
    this->webSocket.setUrl(API_URL);
    this->webSocket.setPingInterval(45);
    this->webSocket.disablePerMessageDeflate();
    this->webSocket.setOnMessageCallback([](const ix::WebSocketMessagePtr& msg) {
        if (msg->type == ix::WebSocketMessageType::Message) {
            log::info("websocket message: {}", msg->str);
        }
    });
    this->webSocket.start();
}