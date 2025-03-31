#include <Geode/Geode.hpp>

#include <managers/APIManager.hpp>

using namespace geode::prelude;

$on_mod(Loaded) {
	APIManager* apiManager;
	apiManager->createUser(GJAccountManager::get()->m_accountID, []() {
		log::debug("Account successfully created!");
	});
}