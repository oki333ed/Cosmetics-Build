#include <Geode/Geode.hpp>

#include <managers/APIManager.hpp>

using namespace geode::prelude;

$on_mod(Loaded) {
	APIManager* apiManager;

	apiManager->getAccount(GJAccountManager::get()->m_accountID, [](Account* account) {
		log::debug("credits amount: {}", account->getCreditsAmount());
	});
	apiManager->getAllCosmetics([](std::vector<Cosmetic*> cosmetics) {
		for (Cosmetic* cosmetic : cosmetics) {
			log::debug("Cosmetic ID: {} - Cosmetic Name: {} - Cosmetic Amount: {}",
				cosmetic->getCosmeticID(), cosmetic->getCosmeticName(), cosmetic->getCosmeticAmount());
		}
	});
	apiManager->createUser(GJAccountManager::get()->m_accountID, []() {
		log::debug("Account successfully created!");
	});
	apiManager->addCosmeticToUser(GJAccountManager::get()->m_accountID, 1001, true, []() {
		log::debug("Cosmetic added successfully!");
	});
}