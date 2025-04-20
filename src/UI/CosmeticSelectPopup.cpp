#include "CosmeticSelectPopup.hpp"

#include <events/EventDispatcher.hpp>
#include <managers/CosmeticManager.hpp>
#include <network/NetworkManager.hpp>
#include <network/packets/Client.hpp>
#include <UIBuilder.hpp>

using namespace geode::prelude;

bool CosmeticSelectPopup::setup(CosmeticsUser& user) {
    this->setTitle("Select Cosmetic");

    auto player = drawPlayer(IconType::Cube, m_mainLayer, user);

    auto shadow = CCSprite::createWithSpriteFrameName("shopKeeper2_eye_01_001.png");
    shadow->setRotationX(80.f);
    player->addChildAtPosition(shadow, Anchor::Bottom);

    NetworkManager::get()->send(RequestAllCosmeticsPacket::create());

    auto eventDispatcher = Cosmetics::EventDispatcher::get();
    eventDispatcher->registerListener(new Cosmetics::Event<std::vector<Cosmetic>>("AllCosmeticsPacket", [player, this](std::vector<Cosmetic> cosmetics) {
        for (auto cosmetic : cosmetics) {
            this->drawAllCosmetics(cosmetics);
        }
    }));

    return true;
}

SimplePlayer* CosmeticSelectPopup::drawPlayer(IconType type, CCNode* baseNode, CosmeticsUser& user) {
    auto gm = GameManager::sharedState();

    auto firstColor = gm->colorForIdx(gm->getPlayerColor());
    auto secondColor = gm->colorForIdx(gm->getPlayerColor2());
    auto glowColor = gm->colorForIdx(gm->getPlayerGlowColor());

    CCPoint offset{50.f, 0.f};

    SimplePlayer* player = SimplePlayer::create(0);
    baseNode->addChildAtPosition(player, Anchor::Left, offset);
    player->updatePlayerFrame(getPlayerIconIndex(type), type);

    player->setColors(firstColor, secondColor);
    player->setGlowOutline(glowColor);
    player->enableCustomGlowColor(glowColor);
    if (!gm->getPlayerGlow()) player->disableGlowOutline();

    if (type == IconType::Ship || type == IconType::Ufo || type == IconType::Jetpack) {
        SimplePlayer* cube = SimplePlayer::create(0);
        cube->setZOrder(-1);
        baseNode->addChildAtPosition(cube, Anchor::Left, offset);
        cube->updatePlayerFrame(getPlayerIconIndex(type), type);
        cube->setColors(firstColor, secondColor);
        cube->setGlowOutline(glowColor);
        cube->enableCustomGlowColor(glowColor);
        if (!gm->getPlayerGlow()) cube->disableGlowOutline();
        CCPoint posCube, posVehicle;
		float scaleCube;
		switch (type) {
			case IconType::Ship: {posCube = ccp(0,5); posVehicle = ccp(0,-5); scaleCube = 0.55; break;}
			case IconType::Ufo: {posCube = ccp(0,5); posVehicle = ccp(0,0); scaleCube = 0.55; break;}
			case IconType::Jetpack: {posCube = ccp(6,4); posVehicle = ccp(0,0); scaleCube = 0.6; break;}
		}
        if (auto glowSpr = player->m_outlineSprite) {
            CCPoint textureOffset = glowSpr->getParent()->getPosition();
			glowSpr->removeFromParent();
			cube->addChild(glowSpr, -1);
			glowSpr->setScale(1 / scaleCube);
			glowSpr->setPosition((posVehicle - posCube + textureOffset) / scaleCube);
        }
        cube->setScale(scaleCube);
        cube->setPosition(posCube);
        player->setPosition(posVehicle);

        auto cosmetics = user.getActiveCosmetics();
        this->drawHat(cosmetics.getHat(), cube);
        this->drawMask(cosmetics.getMask(), cube);
    } else {
        auto cosmetics = user.getActiveCosmetics();
        this->drawHat(cosmetics.getHat(), player);
        this->drawMask(cosmetics.getMask(), player);
    }

    return player;
}

void CosmeticSelectPopup::drawAllCosmetics(std::vector<Cosmetic> cosmetics) {
    for (auto cosmetic : cosmetics) {
        auto btnMenu = Build<CCMenu>::create()
            .layout(SimpleRowLayout::create())
            .collect();

        m_mainLayer->addChildAtPosition(btnMenu, Anchor::Right, {-50.f, 0.f});
    
        auto cosmeticIcon = Build<CCSprite>::createSpriteName(fmt::format("{}.png"_spr, cosmetic.getCosmeticID()).c_str())
            .scale(0.5f)
            .parent(btnMenu)
            .collect();
        
        btnMenu->updateLayout();
    }
}

void CosmeticSelectPopup::drawHat(Cosmetic hat, SimplePlayer* player) {
    if (hat.isEmpty()) {
        return;
    }

    CCSprite* spr;
    auto regularPos = player->m_detailSprite->getScaledContentSize() + CCPoint{-3.f, 2.f};
    auto* regularHat = Build<CCSprite>::createSpriteName(fmt::format("{}.png"_spr, hat.getCosmeticID()).c_str())
        .scale(0.5f)
        .id(fmt::format("hat-{}", hat.getCosmeticID()))
        .parent(player->m_firstLayer)
        .store(spr)
        .pos(regularPos)
        .collect();
}

void CosmeticSelectPopup::drawMask(Cosmetic mask, SimplePlayer* player) {
    if (mask.isEmpty()) {
        return;
    }

    CCSprite* spr;
    auto regularPos = player->m_detailSprite->getScaledContentSize() + CCPoint{6.5f, 6.5f};
    auto* regularMask = Build<CCSprite>::createSpriteName(fmt::format("{}.png"_spr, mask.getCosmeticID()).c_str())
        .scale(0.5f)
        .id(fmt::format("mask-{}", mask.getCosmeticID()))
        .parent(player->m_firstLayer)
        .store(spr)
        .pos(regularPos)
        .collect();
}

int CosmeticSelectPopup::getPlayerIconIndex(IconType type) {
    auto gm = GameManager::sharedState();
    switch(type) {
        case IconType::Cube: return gm->getPlayerFrame();
        case IconType::Ship: return gm->getPlayerShip();
        case IconType::Ball: return gm->getPlayerBall();
        case IconType::Ufo: return gm->getPlayerBird();
        case IconType::Wave: return gm->getPlayerDart();
        case IconType::Robot: return gm->getPlayerRobot();
        case IconType::Spider: return gm->getPlayerSpider();
		case IconType::Swing: return gm->getPlayerSwing(); 
		case IconType::Jetpack: return gm->getPlayerJetpack();
        default: return gm->getPlayerFrame();
    }
}

CosmeticSelectPopup* CosmeticSelectPopup::create(CosmeticsUser& user) {
    auto ret = new CosmeticSelectPopup();
    if (ret->initAnchored(400.f, 250.f, user)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr; 
}