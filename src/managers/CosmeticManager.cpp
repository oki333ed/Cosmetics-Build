#include "CosmeticManager.hpp"

ActiveCosmetics CosmeticManager::activeCosmeticsFromJSON(matjson::Value value) {
    return ActiveCosmetics(
        (!value["hat"].isNull()) ? Cosmetic(value["hat"]) : Cosmetic(),
        (!value["mask"].isNull()) ? Cosmetic(value["mask"]) : Cosmetic(),
        (!value["object"].isNull()) ? Cosmetic(value["object"]) : Cosmetic(),
        (!value["particle"].isNull()) ? Cosmetic(value["particle"]) : Cosmetic()
    );
}