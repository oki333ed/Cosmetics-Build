#include <defs.hpp>
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>

#include <managers/CosmeticManager.hpp>
#include <network/packets/Client.hpp>
#include <network/NetworkManager.hpp>

#include <argon/argon.hpp>

using namespace geode::prelude;

$on_mod(Loaded) {
    NetworkManager* networkManager = NetworkManager::get();
    networkManager->init();
}

$on_game(Loaded) {
	NetworkManager* networkManager = NetworkManager::get();

	if (networkManager->connected()) {
		// auth
		auto res = argon::startAuth([networkManager](Result<std::string> res) {
			if (!res) {
				log::warn("Argon Auth failed: {}", res.unwrapErr());
				return;
			}

			auto token = std::move(res).unwrap();
			networkManager->send(CreateUserPacket::create(GJAccountManager::get()->m_accountID, token));
		}, [](argon::AuthProgress progress) {
			log::info("Auth progress: {}", argon::authProgressToString(progress));
		});

		if (!res) {
			log::warn("Failed to start auth attempt: {}", res.unwrapErr());
		} else {
			res.unwrap();
		}
	}
}

class $modify(MenuLayer) {
	bool init() {
		MenuLayer::init();
		

		return true;
	}
};