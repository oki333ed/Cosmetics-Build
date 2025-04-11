#pragma once

#include <Geode/modify/PlayLayer.hpp>

struct HookedPlayLayer : geode::Modify<HookedPlayLayer, PlayLayer> {
    $override
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects);
};