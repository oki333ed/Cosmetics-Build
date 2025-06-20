#pragma once

using namespace geode::prelude;

#include <Geode/Geode.hpp>

class CosmeticLayer : public cocos2d::CCLayer {
public:
    virtual bool init();

    void onBack(cocos2d::CCObject*);
    static CCScene* scene();
    static CosmeticLayer* create();
};