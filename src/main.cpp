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
		NetworkManager* networkManager = NetworkManager::get();

		CreateUserPacket createUserPacket = CreateUserPacket::create(GJAccountManager::get()->m_accountID);
		networkManager->send(createUserPacket);

		RequestUserPacket requestUserPacket = RequestUserPacket::create(GJAccountManager::get()->m_accountID);
		networkManager->send(requestUserPacket);

		return true;
	}
};