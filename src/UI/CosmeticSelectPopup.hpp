#pragma once

#include <Geode/Geode.hpp>

#include <types/User.hpp>

class CosmeticSelectPopup : public geode::Popup<CosmeticsUser&> {
protected:
    bool setup(CosmeticsUser& user) override;

public:
    static CosmeticSelectPopup* create(CosmeticsUser& user);
};