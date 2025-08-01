#pragma once

#include <Geode/loader/Event.hpp>

#include <types/Cosmetic.hpp>

#include <vector>

class AllCosmeticsEvent : public geode::Event {
protected:
    std::vector<FullCosmetic> m_cosmetics;

public:
    AllCosmeticsEvent(std::vector<FullCosmetic> const& cosmetics) : m_cosmetics(cosmetics) {}

    std::vector<FullCosmetic> getCosmetics() const {
        return m_cosmetics;
    }
};

class UserCosmeticsEvent : public geode::Event {
protected:
    ActiveCosmetics m_cosmetics;

public:
    UserCosmeticsEvent(ActiveCosmetics const& cosmetics) : m_cosmetics(cosmetics) {}

    ActiveCosmetics getCosmetics() const {
        return m_cosmetics;
    }
};

class CosmeticSetActiveEvent : public geode::Event {
protected:
    struct PacketRes {
        int code;
        std::string message;
    };

    PacketRes res;

public:
    CosmeticSetActiveEvent(int code, std::string message) : res({code, message}) {}

    PacketRes getPacketRes() const {
        return res;
    }
};