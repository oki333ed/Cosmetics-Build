#include <defs.hpp>
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>

#include <managers/CosmeticManager.hpp>
#include <network/packets/Client.hpp>
#include <network/NetworkManager.hpp>

#include <argon/argon.hpp>

using namespace geode::prelude;

$on_game(Loaded) {
	NetworkManager* networkManager = NetworkManager::get();
    networkManager->init();
}

class $modify(MenuLayer) {
	bool init() {
		MenuLayer::init();
		
		return true;
	}
};