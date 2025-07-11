#include "CosmeticLayer.hpp"

#include <events/Cosmetic.hpp>
#include <managers/CosmeticManager.hpp>
#include <network/NetworkManager.hpp>
#include <network/packets/Client.hpp>
#include <types/Cosmetic.hpp>
#include <types/CosmeticPlayer.hpp>

#include <UIBuilder.hpp>

using namespace geode::prelude;

bool CosmeticLayer::init() {
    if(!CCLayer::init()) return false;
    auto winSize = CCDirector::get()->getWinSize();
    auto gm = GameManager::sharedState();

    CCMenu* m_menu = CCMenu::create();
    m_menu->setPosition({0, 0});
    m_menu->setID("menu");
    addChild(m_menu, 100);

    CCSprite* backSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    CCMenuItemSpriteExtra* backBtn = CCMenuItemSpriteExtra::create(backSpr, this, menu_selector(CosmeticLayer::onBack));
    backBtn->setPosition({25.f, winSize.height - 25.f});
    m_menu->addChild(backBtn);

    auto bgLayer = CCLayer::create();
    bgLayer->setID("background-layer");
    bgLayer->setAnchorPoint({0.79f, 0.4f});
    addChild(bgLayer, -1);

    auto m_bg = CCSprite::create("game_bg_01_001.png");
    m_bg->setColor({90, 170, 255});
    m_bg->setID("gd-background");
    m_bg->setPosition({480, 380.f});
    bgLayer->addChild(m_bg, 0);

    auto bg2 = CCSprite::create("game_bg_01_001.png");
    bg2->setColor({90, 170, 255});
    bg2->setPosition({768, 256.f});
    m_bg->addChild(bg2, 0);

    auto bgMove = CCMoveBy::create(5.0f, {-512.f, 0.f});
    auto bgReset = CCMoveTo::create(0.0f, {480.f, 380.f});
    auto bgSeq = CCSequence::create(bgMove, bgReset, nullptr);
    auto bgRepeat = CCRepeatForever::create(bgSeq);
    m_bg->runAction(bgRepeat);

    auto groundLayer = GJGroundLayer::create(1, 1);
    groundLayer->setPosition({winSize.width - 359.f, 130.f});
    bgLayer->addChild(groundLayer, 1);

    auto groundMove = CCMoveBy::create(0.5f, {-128.f, 0.f});
    auto groundReset = CCMoveTo::create(0.0f, {0, 0});
    auto groundSeq = CCSequence::create(groundMove, groundReset, nullptr);
    auto groundRepeat = CCRepeatForever::create(groundSeq);
    groundLayer->getChildByID("ground-sprites")->runAction(groundRepeat);

    // player
    CosmeticsSimplePlayer* player = static_cast<CosmeticsSimplePlayer*>(CosmeticsSimplePlayer::create(0));

    auto m_firstColor = gm->colorForIdx(gm->getPlayerColor());
    auto m_secondColor = gm->colorForIdx(gm->getPlayerColor2());
    auto m_glowColor = gm->colorForIdx(gm->getPlayerGlowColor());

    player->updatePlayerFrame(gm->getPlayerFrame(), IconType::Cube);
    player->setColors(m_firstColor, m_secondColor);
    player->setGlowOutline(m_glowColor);
    player->enableCustomGlowColor(m_glowColor);
    if (!gm->getPlayerGlow()) player->disableGlowOutline();
    player->setPosition({winSize.width - 120.f, 146.f});

    auto activeCosmetics = CosmeticManager::get()->getSelfUser().getActiveCosmetics();
    player->drawCosmetics(activeCosmetics, m_firstColor, m_secondColor, m_glowColor);
    bgLayer->addChild(player, 5);
  
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

    auto logoLabel = CCSprite::create("cosmeticsLabel.png"_spr);
    logoLabel->setPosition({winSize.width / 2, winSize.height - 25.f});
    logoLabel->setScale(1.15f);
    addChild(logoLabel, 5);

    auto infoMenu = CCMenu::create();
    infoMenu->setContentSize({180.f, 100.f});
    infoMenu->setAnchorPoint({0.5, 0.5});
    infoMenu->setVisible(false);
    infoMenu->setPosition({winSize.width - 200.f, 10.f});
    addChild(infoMenu, 5);

    auto m_infoContainer = CCScale9Sprite::create("square02_001.png");
    m_infoContainer->setContentSize({180.f, 100.f});
    m_infoContainer->setPosition({infoMenu->getContentWidth() / 2, infoMenu->getContentHeight() / 2});
    m_infoContainer->setOpacity(100);
    infoMenu->addChild(m_infoContainer, 3);

    auto m_titleText = CCLabelBMFont::create("cosmeticName", "bigFont.fnt");
    m_titleText->setPosition({m_infoContainer->getContentWidth() / 2, 88.f});
    m_titleText->setColor({255, 255, 255});
    m_titleText->setScale(0.5f);
    infoMenu->addChild(m_titleText, 5);

    auto infoLine = CCSprite::createWithSpriteFrameName("edit_vLine_001.png");
    infoLine->setScaleX(0.5f);
    infoLine->setScaleY(infoMenu->getContentWidth() / 90.f);
    infoLine->setRotation(90);
    infoLine->setPosition({infoMenu->getContentWidth() / 2, 75.f});
    infoMenu->addChild(infoLine, 3);

    auto m_descText = CCLabelBMFont::create("cosmeticDescription", "bigFont.fnt");
    m_descText->setPosition({infoMenu->getContentWidth() / 2, 65.f});
    m_descText->setColor({255, 255, 255});
    m_descText->limitLabelWidth(170.f, 0.3f, 0.1f);
    infoMenu->addChild(m_descText, 5);

    Build<CCSprite>::createSpriteName("GJ_editModeBtn_001.png")
        .scale(0.5f)
        .intoMenuItem([this, bgLayer]() {})
        .pos({infoMenu->getContentWidth() / 2 - 60.f, 35.f})
        .parent(infoMenu);

    Build<IconButtonSprite>::create("GJ_square07.png", CCSprite::createWithSpriteFrameName("GJ_plus3Btn_001.png"), "equip", "bigFont.fnt")
        .scale(0.75f)
        .intoMenuItem([this, bgLayer]() {})
        .pos({infoMenu->getContentWidth() / 2, 35})
        .parent(infoMenu);

    Build<CCSprite>::createSpriteName("GJ_paintBtn_001.png")
        .scale(0.5f)
        .intoMenuItem([this, bgLayer]() {})
        .pos({infoMenu->getContentWidth() / 2 + 60.f, 35.f})
        .parent(infoMenu);

    auto menu = CCMenu::create();
    menu->setContentSize({winSize.width - 240.f, 260});
    menu->setPosition({20, 10});
    addChild(menu, 3);

    auto m_container = CCScale9Sprite::create("square02_001.png");
    m_container->setContentSize({menu->getContentWidth(), 260});
    m_container->setPosition({menu->getContentWidth() / 2, menu->getContentHeight() / 2});
    m_container->setOpacity(100);
    menu->addChild(m_container, 3);

    auto categoryLine = CCSprite::createWithSpriteFrameName("edit_vLine_001.png");
    categoryLine->setScaleX(0.5f);
    categoryLine->setScaleY(menu->getContentWidth() / 90.f);
    categoryLine->setRotation(90);
    categoryLine->setPosition({menu->getContentWidth() / 2, 233.f});
    menu->addChild(categoryLine, 3);

    auto m_categoryMenu = CCMenu::create();
    m_categoryMenu->setContentSize({menu->getContentWidth() - 10.f, 30});
    m_categoryMenu->setLayout(AxisLayout::create()->setGap(5)->setAutoScale(false));
    m_categoryMenu->setPosition({menu->getContentWidth() / 2, 247.f});
    menu->addChild(m_categoryMenu, 3);

    auto categoryHats = IconButtonSprite::create("GJ_square07.png", CCSprite::createWithSpriteFrameName("d_heart01_001.png"), "hats", "bigFont.fnt");
    categoryHats->setScale(0.5f);
    m_categoryMenu->addChild(categoryHats, 5);

    auto categoryMasks = IconButtonSprite::create("GJ_square07.png", CCSprite::createWithSpriteFrameName("d_heart01_001.png"), "masks", "bigFont.fnt");
    categoryMasks->setScale(0.5f);
    m_categoryMenu->addChild(categoryMasks, 5);

    auto categoryObjects = IconButtonSprite::create("GJ_square07.png", CCSprite::createWithSpriteFrameName("d_heart01_001.png"), "objects", "bigFont.fnt");
    categoryObjects->setScale(0.5f);
    m_categoryMenu->addChild(categoryObjects, 5);

    auto categoryPets = IconButtonSprite::create("GJ_square07.png", CCSprite::createWithSpriteFrameName("d_heart01_001.png"), "pets", "bigFont.fnt");
    categoryPets->setScale(0.5f);
    m_categoryMenu->addChild(categoryPets, 5);
    m_categoryMenu->updateLayout();

    Ref<ScrollLayer> cosmeticScroll = ScrollLayer::create({menu->getContentWidth() - 10.f, 228}, true, true);
    cosmeticScroll->getChildByID("content-layer")->setLayout(AxisLayout::create());
    cosmeticScroll->setAnchorPoint({0.5, 1});
    cosmeticScroll->setPosition({5.f, 0.f});
    menu->addChild(cosmeticScroll, 4);

    Ref<CCMenu> cosmeticMenu = CCMenu::create();
    cosmeticMenu->setContentSize({menu->getContentWidth() - 10.f, 228});
    cosmeticMenu->setAnchorPoint({0.5, 1.f});
    cosmeticMenu->setPosition({cosmeticScroll->getContentWidth() / 2, 228.f});
    cosmeticMenu->setLayout(AxisLayout::create()->setGap(5)->setGrowCrossAxis(true));
    cosmeticScroll->getChildByID("content-layer")->addChild(cosmeticMenu, 5);

    auto nm = NetworkManager::get();
    auto cm = CosmeticManager::get();
    nm->send(RequestAllCosmeticsPacket::create());

    auto listener = new EventListener<EventFilter<AllCosmeticsEvent>>([bgLayer, infoMenu, cosmeticMenu, cosmeticScroll, cm, m_firstColor, m_secondColor, m_glowColor, m_titleText, m_descText, m_infoContainer, player, activeCosmetics](AllCosmeticsEvent* ev) {
        for (auto cosmetic : ev->getCosmetics()) {
            log::info("cosmetic: {}", cosmetic.createObject().dump());

            auto spr = CCLayer::create();
            spr->setID(fmt::format("cosmetic-{}", cosmetic.getCosmeticID()));
            spr->setContentSize({50.f, 50.f});

            auto outline = CCScale9Sprite::create("GJ_square07.png");
            outline->setContentSize({55.f, 55.f});
            outline->setPosition({25.f, 25.f});
            spr->addChild(outline, 4);

            auto rarityColor = CCLayerColor::create({ 0, 255, 255, 255 });
            rarityColor->setContentSize({47.f, 2.f});
            rarityColor->setPosition({1.5f, 1.f});
            spr->addChild(rarityColor, 3);

            auto rarityGradient = CCLayerGradient::create(
              ccc4(0, 50, 50, 200), ccc4(0, 0, 0, 0)
            );
            rarityGradient->setContentSize({50.f, 50.f});
            rarityGradient->setPosition({0, 0});
            rarityGradient->setVector({0, 1});
            spr->addChild(rarityGradient, 2);
            
            switch (cosmetic.typeFromID()) {
                case Hat: {
                    Build(cm->loadHat(cosmetic.getCosmeticID(), m_firstColor, m_secondColor, m_glowColor))
                        .pos(25.f, 22.5f)
                        .scale(0.8f)
                        .zOrder(2)
                        .parent(spr);
                    break;
                }

                case Mask: {
                    Build(cm->loadMask(cosmetic.getCosmeticID(), m_firstColor, m_secondColor, m_glowColor))
                        .pos(25.f, 22.5f)
                        .scale(0.425f)
                        .zOrder(2)
                        .parent(spr);
                    break;
                }

                default: {
                    break;
                }
            }

            auto btn = Build(spr)
                .intoMenuItem([bgLayer, infoMenu, m_titleText, m_descText, m_infoContainer, cosmetic, player, m_firstColor, m_secondColor, m_glowColor, activeCosmetics]() {
                    m_titleText->setString(cosmetic.getCosmeticName().c_str());
                    m_descText->setString(cosmetic.getCosmeticDescription().c_str());
                    m_infoContainer->updateLayout();
                    m_infoContainer->getChildByType<CCSpriteBatchNode>(0)->setPosition({0.f, 0.f});

                    switch (cosmetic.typeFromID()) {
                        case Hat: {
                            player->drawHat(cosmetic, m_firstColor, m_secondColor, m_glowColor);
                            break;
                        }

                        case Mask: {
                            player->drawMask(cosmetic, m_firstColor, m_secondColor, m_glowColor);
                            break;
                        }

                        default: {
                            break;
                        }
                    }

                    infoMenu->setVisible(true);
                    bgLayer->runAction(CCSequence::create(CCEaseSineInOut::create(CCScaleTo::create(0.5f, 2.f)), nullptr));
                })
                .contentSize(spr->getContentSize())
                .collect();
            
            btn->setPosition({25.f, 25.f});
            spr->setPosition({0.f, 0.f});
            spr->setScale(0.8f);

            auto menu = CCMenu::create();
            menu->setContentSize({50.f, 50.f});
            menu->addChild(btn);

            cosmeticMenu->addChild(menu, 3);
        }

        cosmeticMenu->updateLayout();
        cosmeticScroll->getChildByID("content-layer")->updateLayout();
        cosmeticScroll->scrollToTop();
            
        return ListenerResult::Propagate;
    });

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
