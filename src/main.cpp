#include <Geode/Geode.hpp>

#include <Geode/utils/web.hpp>

using namespace geode::prelude;

$on_mod(Loaded) {
	web::WebRequest req = web::WebRequest();

	req.param("accountID", GJAccountManager::get()->m_accountID);
	req.get("http://127.0.0.1:8787/api/getAccount").listen([](web::WebResponse* res) {
		if (!res->ok()) {
			log::error("uh oh: {}", res->code());
		} else {
			auto json = res->json().unwrapOr(nullptr);
			if (json != nullptr) {
				log::info("funny json: {}", json.asArray().unwrap()[0]["accountID"].asInt().unwrap());
			}
		}
	}, [](auto progress) {}, [] {});
}