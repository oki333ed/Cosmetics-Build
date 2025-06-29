#pragma once

#include <Geode/Geode.hpp>

class CosmeticLayer : public cocos2d::CCLayer {
protected:
    virtual bool init();

    void onBack(cocos2d::CCObject*);
    static CosmeticLayer* create();
public:
    static cocos2d::CCScene* scene();
};