#include "APIManager.hpp"

#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

void APIManager::addCosmeticToUser(int accountID, int cosmeticID, bool isActive, std::function<void()> func) {
    web::WebRequest req = web::WebRequest();
    matjson::Value body = matjson::Value();
    body.set("accountID", accountID);
    body.set("cosmeticID", cosmeticID);
    body.set("isActive", (isActive) ? 1 : 0);
    req.bodyJSON(body);
    req.post(fmt::format("{}/api/addCosmeticToUser", API_URL)).listen([func](web::WebResponse* res) {
        if (!res->ok()) {
            log::error("APIManager addCosmeticToUser returned code: {}", res->code());
        } else {
            func();
        }
    });
}

void APIManager::createUser(int accountID, std::function<void()> func) {
    web::WebRequest req = web::WebRequest();
    matjson::Value body = matjson::Value();
    body.set("accountID", accountID);
    req.bodyJSON(body);
    req.post(fmt::format("{}/api/createUser", API_URL)).listen([func](web::WebResponse* res) {
        if (!res->ok()) {
            log::error("APIManager createUser returned code: {}", res->code());
        } else {
            func();
        }
    });
}

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

void APIManager::setCosmeticActive(int accountID, int cosmeticID, std::function<void()> func) {
    web::WebRequest req = web::WebRequest();
    matjson::Value body = matjson::Value();
    body.set("accountID", accountID);
    body.set("cosmeticID", cosmeticID);
    req.bodyJSON(body);
    req.post(fmt::format("{}/api/setCosmeticActive", API_URL)).listen([func](web::WebResponse* res) {
        if (!res->ok()) {
            log::error("APIManager setCosmeticActive returned code: {}", res->code());
        } else {
            func();
        }
    }, [](auto progress) {}, [] {});
}