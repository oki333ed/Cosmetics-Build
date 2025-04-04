#include <Geode/Geode.hpp>

#include <network/packets/Client.hpp>
#include <network/NetworkManager.hpp>

using namespace geode::prelude;

$on_mod(Loaded) {
    NetworkManager* networkManager = NetworkManager::get();
    networkManager->init();
    
    AddCosmeticPacket addCosmeticPacket(1003, true);
    networkManager->send(addCosmeticPacket);
}