#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>

#include <managers/CosmeticManager.hpp>
#include <network/packets/Client.hpp>
#include <network/NetworkManager.hpp>

using namespace geode::prelude;

$on_mod(Loaded) {
    NetworkManager* networkManager = NetworkManager::get();
    networkManager->init();
}

class $modify(MenuLayer) {
	bool init() {
		MenuLayer::init();
		NetworkManager* networkManager = NetworkManager::get();

		if (networkManager->connected()) {
			AddCosmeticPacket addCosmeticPacket = AddCosmeticPacket::create(GJAccountManager::get()->m_accountID, 2001, true);
			networkManager->send(addCosmeticPacket);

			CreateUserPacket createUserPacket = CreateUserPacket::create(GJAccountManager::get()->m_accountID);
			networkManager->send(createUserPacket);
		}

		return true;
	}
};