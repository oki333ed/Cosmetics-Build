#pragma once

#include <Geode/modify/GJGarageLayer.hpp>

#include <UI/CosmeticSelectPopup.hpp>

struct HookedGJGarageLayer : geode::Modify<HookedGJGarageLayer, GJGarageLayer> {
    $override
    bool init();
};