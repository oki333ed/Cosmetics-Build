#include <Geode/loader/Event.hpp>

#include <types/Cosmetic.hpp>

#include <vector>

class CosmeticLayerEvent : public geode::Event {
protected:
    std::vector<FullCosmetic> m_cosmetics;

public:
    CosmeticLayerEvent(std::vector<FullCosmetic> const& cosmetics);

    std::vector<FullCosmetic> getCosmetics() const {
        return m_cosmetics;
    }
};