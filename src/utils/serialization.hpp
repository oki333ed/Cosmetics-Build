#pragma once

#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/archives/json.hpp>

#define SERIALIZE(...) \
    template<class Archive> \
    void serialize(Archive& ar) {ar(__VA_ARGS__);}