#pragma once

#include <string>
#include <typeinfo>

#include <matjson.hpp>

template <typename Derived, size_t PacketId>
class Packet {
public:
    matjson::Value encode() const {
        return matjson::makeObject({
            {"packetID", PacketId},
            {"data", static_cast<const Derived*>(this)->encodeData()}
        });
    }

    size_t getPacketID() const {
        return PacketId;
    }
};