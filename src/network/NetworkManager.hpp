#pragma once

class NetworkManager {
public:
    static NetworkManager* get() {
        static NetworkManager instance;
        return &instance;
    }

    void init();
};