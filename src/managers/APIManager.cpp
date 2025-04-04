#include "APIManager.hpp"

#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

void APIManager::getAccount(int accountID, std::function<void(Account*)> func) {
    web::WebRequest req = web::WebRequest();
	req.param("accountID", GJAccountManager::get()->m_accountID);
	req.get(fmt::format("{}/api/getAccount", API_URL)).listen([func](web::WebResponse* res) {
		if (!res->ok()) {
			log::error("APIManager getAccount returned code: {}", res->code());
		} else {
			auto json = res->json().unwrapOr(nullptr);
			if (json != nullptr) {
                func(new Account(json.asArray().unwrap()[0]));
			}
		}
	}, [](auto progress) {}, [] {});
}

void APIManager::getAllCosmetics(std::function<void(std::vector<Cosmetic*>)> func) {
    web::WebRequest req = web::WebRequest();
    req.get(fmt::format("{}/api/cosmetics", API_URL)).listen([func](web::WebResponse* res) {
        if (!res->ok()) {
            log::error("APIManager getAllCosmetics returned code: {}", res->code());
        } else {
            auto json = res->json().unwrapOr(nullptr);
            if (json != nullptr) {
                std::vector<Cosmetic*> cosmetics;
                for (auto object : json.asArray().unwrap()) {
                    cosmetics.push_back(new Cosmetic(object));
                }
                func(cosmetics);
            }
        }
    }, [](auto progress) {}, [] {});
}