#include "CosmeticManager.hpp"
#include "hooks/PlayerObject.hpp"

ActiveCosmetics CosmeticManager::activeCosmeticsFromJSON(matjson::Value value) {
    return ActiveCosmetics(
        (!value["hat"].isNull()) ? Cosmetic(value["hat"]) : Cosmetic(),
        (!value["mask"].isNull()) ? Cosmetic(value["mask"]) : Cosmetic(),
        (!value["object"].isNull()) ? Cosmetic(value["object"]) : Cosmetic(),
        (!value["particle"].isNull()) ? Cosmetic(value["particle"]) : Cosmetic()
    );
}

void CosmeticManager::setDualCosmetics(ActiveCosmetics cosmetics, PlayerObject* p1, PlayerObject* p2) {
    static_cast<CosmeticsPlayerObject*>(p1)->setCosmetics(cosmetics);
    static_cast<CosmeticsPlayerObject*>(p2)->setCosmetics(cosmetics);
}