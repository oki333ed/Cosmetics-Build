#include "CosmeticSelectPopup.hpp"

bool CosmeticSelectPopup::setup(CosmeticsUser& user) {
    this->setTitle("Select Cosmetic");

    

    return true;
}

CosmeticSelectPopup* CosmeticSelectPopup::create(CosmeticsUser& user) {
    auto ret = new CosmeticSelectPopup();
    if (ret->initAnchored(400.f, 250.f, user)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr; 
}