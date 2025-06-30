#include "CosmeticLayer.hpp"

#include <events/EventDispatcher.hpp>
#include <network/NetworkManager.hpp>
#include <network/packets/Client.hpp>
#include <types/Cosmetic.hpp>

using namespace geode::prelude;
using namespace Cosmetics;

bool CosmeticLayer::init() {
    if(!CCLayer::init()) return false;
    auto winSize = CCDirector::get()->getWinSize();
    auto gm = GameManager::sharedState();

    CCMenu* m_menu = CCMenu::create();
    m_menu->setPosition({24,297});
    addChild(m_menu, 100);

    CCSprite* backSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    CCMenuItemSpriteExtra* backBtn = CCMenuItemSpriteExtra::create(backSpr, this, menu_selector(CosmeticLayer::onBack));
    m_menu->addChild(backBtn);

    // gd background
    auto m_bg = CCSprite::create("game_bg_01_001.png");
    m_bg->setColor({90, 170, 255});
    m_bg->setID("gd-background");
    m_bg->setPosition({480, 380.f});
    addChild(m_bg, 0);

    auto bg2 = CCSprite::create("game_bg_01_001.png");
    bg2->setColor({90, 170, 255});
    bg2->setPosition({768, 256.f});
    m_bg->addChild(bg2, 0);

    auto bgMove = CCMoveBy::create(5.0f, {-512.f, 0.f});
    auto bgReset = CCMoveTo::create(0.0f, {480.f, 380.f});
    auto bgSeq = CCSequence::create(bgMove, bgReset, nullptr);
    auto bgRepeat = CCRepeatForever::create(bgSeq);
    m_bg->runAction(bgRepeat);

    // gd ground
    auto groundLayer = GJGroundLayer::create(1, 1); // idk what these numbers mean but it works lol
    groundLayer->setPosition({winSize.width - 359.f, 130.f});
    addChild(groundLayer, 1);

    auto groundMove = CCMoveBy::create(0.5f, {-128.f, 0.f});
    auto groundReset = CCMoveTo::create(0.0f, {0, 0});
    auto groundSeq = CCSequence::create(groundMove, groundReset, nullptr);
    auto groundRepeat = CCRepeatForever::create(groundSeq);
    groundLayer->getChildByID("ground-sprites")->runAction(groundRepeat);

    // player
    SimplePlayer* player = SimplePlayer::create(0);

    auto m_firstColor = gm->colorForIdx(gm->getPlayerColor());
    auto m_secondColor = gm->colorForIdx(gm->getPlayerColor2());
    auto m_glowColor = gm->colorForIdx(gm->getPlayerGlowColor());

    player->updatePlayerFrame(gm->getPlayerFrame(), IconType::Cube);
    player->setColors(m_firstColor, m_secondColor);
    player->setGlowOutline(m_glowColor);
    player->enableCustomGlowColor(m_glowColor);
    if (!gm->getPlayerGlow()) player->disableGlowOutline();
    player->setPosition({winSize.width - 120.f, 146.f});
    addChild(player, 5);

    // gray background
    auto m_background = CCLayerColor::create({25, 25, 25, 255}, winSize.width, winSize.height);
    m_background->setContentWidth(winSize.width - 360.f);
    m_background->setID("background");
    addChild(m_background, 2);

    auto gradient = CCLayerGradient::create(
        ccc4(25, 25, 25, 255), ccc4(0, 0, 0, 0)
    );
    gradient->setContentSize(m_bg->getContentSize());
    gradient->setPosition(winSize.width - 360.f, 0.f);
    gradient->setAnchorPoint({0, 0.5f});
    gradient->setVector({1, 0});
    addChild(gradient, 2);

    auto m_container = CCScale9Sprite::create("square02_001.png");
    m_container->setContentSize({winSize.width / 2, 260});
    m_container->setPosition({winSize.width / 2 - 120, 140});
    m_container->setOpacity(100);
    addChild(m_container, 3);

    auto m_infoContainer = CCScale9Sprite::create("square02_001.png");
    m_infoContainer->setContentSize({winSize.width / 2 - 70.f, 100.f});
    m_infoContainer->setPosition({winSize.width / 1.27f, 60});
    m_infoContainer->setOpacity(100);
    addChild(m_infoContainer, 3);

    auto m_categoryMenu = CCMenu::create();
    m_categoryMenu->setContentSize({winSize.width / 2 - 10.f, 30});
    m_categoryMenu->setLayout(AxisLayout::create()->setGap(5)->setAxisAlignment(AxisAlignment::Start)->setAutoScale(false));
    m_categoryMenu->setPosition({winSize.width / 2 - 120, 253.5f});
    addChild(m_categoryMenu, 3);

    auto category = IconButtonSprite::create("GJ_square07.png", CCSprite::createWithSpriteFrameName("d_heart01_001.png"), "category", "bigFont.fnt");
    category->setScale(0.65f);
    m_categoryMenu->addChild(category, 5);
    m_categoryMenu->updateLayout();

    auto cosmeticMenu = ScrollLayer::create({winSize.width / 2, 230}, true, true);
    cosmeticMenu->getChildByID("content-layer")->setLayout(AxisLayout::create()->setGap(5)->setGrowCrossAxis(true));
    cosmeticMenu->setAnchorPoint({0.5, 1});
    cosmeticMenu->setPosition({winSize.width / 4 - 120.f, 10.f});
    addChild(cosmeticMenu, 4);

    // buttons test
    for (int i = 0; i < 50; ++i) {
        auto spr = CCLayer::create();
        spr->setContentSize({50, 50});
        cosmeticMenu->getChildByID("content-layer")->addChild(spr, 3);

        auto test = CCScale9Sprite::create("GJ_square07.png");
        test->setContentSize({100, 100});
        test->setScale(0.5f);
        test->setPosition({spr->getContentWidth() / 2, spr->getContentHeight() / 2});
        spr->addChild(test, 4);

        auto rarityColor = CCLayerColor::create({ 0, 255, 255, 255 });
        rarityColor->setContentSize({47, 2});
        rarityColor->setPosition({1.5f, 1});
        spr->addChild(rarityColor, 3);

        auto rarityGradient = CCLayerGradient::create(
            ccc4(0, 50, 50, 200), ccc4(0, 0, 0, 0)
        );
        rarityGradient->setContentSize({47, 47});
        rarityGradient->setPosition({1.5f, 1.5f});
        rarityGradient->setVector({0, 1});
        spr->addChild(rarityGradient, 2);
    }

    cosmeticMenu->getChildByID("content-layer")->updateLayout();
    cosmeticMenu->scrollToTop();

    auto nm = NetworkManager::get();
    nm->send(RequestAllCosmeticsPacket::create());

    EventDispatcher::get()->registerListener(new Cosmetics::Event<std::vector<FullCosmetic>>("AllCosmeticsPacket", [](std::vector<FullCosmetic> cosmetics) {
        for (auto cosmetic : cosmetics) {
            log::info("cosmetic: {} - {}", cosmetic.getCosmeticID(), (int)cosmetic.getCosmeticRarity());
        }
    }));

    return true;
}

void CosmeticLayer::onBack(cocos2d::CCObject* sender) {
    auto director = CCDirector::get();
    director->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
}


CCScene* CosmeticLayer::scene() {
    auto layer = CosmeticLayer::create();
    layer->setID("cosmetic-layer");
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
}

CosmeticLayer* CosmeticLayer::create() {
    auto ret = new CosmeticLayer();
    if (ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}