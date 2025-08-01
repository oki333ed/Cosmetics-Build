#pragma once

#include <Geode/Geode.hpp>

#include <types/Cosmetic.hpp>

class CosmeticLayer : public cocos2d::CCLayer {
protected:
    virtual bool init();

    void onBack(cocos2d::CCObject*);
    static CosmeticLayer* create();

    Cosmetic selectedCosmetic;
public:
    static cocos2d::CCScene* scene();
};
