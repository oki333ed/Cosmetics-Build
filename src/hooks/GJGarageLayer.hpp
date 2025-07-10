#pragma once

#include <Geode/modify/GJGarageLayer.hpp>

struct HookedGJGarageLayer : geode::Modify<HookedGJGarageLayer, GJGarageLayer> {
    $override
    bool init();
};