#include <Geode/Geode.hpp>
#include <Geode/modify//MenuLayer.hpp>

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

		RequestUserPacket requestUserPacket = RequestUserPacket::create(GJAccountManager::get()->m_accountID);
		NetworkManager::get()->send(requestUserPacket);

		return true;
	}
};