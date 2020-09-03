#include "GameScene.h"
USING_NS_CC;

bool GameScene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	InitPlayer();
	InitButtons();
	return true;
}

void GameScene::ButtonShootCallback(cocos2d::Ref* sender)
{
	Director::getInstance()->replaceScene(MenuScene::createScene());
}

void GameScene::InitPlayer()
{
	Sprite* sprite = Sprite::create("images/Player/PlayerIdle.png");
	sprite->setPosition(Vec2(VISIBLESIZE.width / 2 + ORIGIN.x, ORIGIN.y));
	PlayerBody = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height));
	PlayerBody->setDynamic(true);
	PlayerBody->setGravityEnable(false);

	Player->addComponent(PlayerBody);
	Player->addChild(sprite, 0, "Idle");
	static_cast<Sprite*>(Player->getChildByName("Idle"))->setVisible(false);
	this->addChild(Player);
}

void GameScene::InitButtons()
{
	const float LocalButtonScale = 0.5f;
	ui::Button* Left = ui::Button::create("images/Buttons/MotionInLeft_Normal.png", "images/Buttons/MotionInLeft_Selected.png", "images/Buttons/MotionInLeft_Normal.png");
	Left->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType e) {
		switch (e)
		{
		case ui::Widget::TouchEventType::BEGAN:
			PlayerBody->setVelocity(Vec2(-300, 0));
			break;
		case ui::Widget::TouchEventType::ENDED:
		case ui::Widget::TouchEventType::CANCELED:
			if (PlayerBody->getVelocity() == Vec2(-300, 0))
			{
				PlayerBody->setVelocity(Vec2(0, 0));
			}
			break;
		default:
			break;
		}
		});
	Left->setScale(GLOBALSCALE + LocalButtonScale);
	const float x = ORIGIN.x;
	const float y = ORIGIN.y + Left->getContentSize().height * (GLOBALSCALE + LocalButtonScale) / 2.f;
	Left->setPosition(Vec2(x + Left->getContentSize().width * (GLOBALSCALE + LocalButtonScale) / 2.f, y));
	ui::Button* Right = ui::Button::create("images/Buttons/MotionInLeft_Normal.png", "images/Buttons/MotionInLeft_Selected.png", "images/Buttons/MotionInLeft_Normal.png");
	Right->setFlippedX(true);
	Right->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType  e) {
		switch (e)
		{
		case ui::Widget::TouchEventType::BEGAN:
			PlayerBody->setVelocity(Vec2(300, 0));
			break;
		case ui::Widget::TouchEventType::ENDED:
		case ui::Widget::TouchEventType::CANCELED:
			if (PlayerBody->getVelocity() == Vec2(300, 0))
			{
				PlayerBody->setVelocity(Vec2(0, 0));
			}
			break;
		default:
			break;
		}
		});
	Right->setScale(GLOBALSCALE + LocalButtonScale);
	Right->setPosition(Left->getPosition() + Vec2(Right->getContentSize().height * (GLOBALSCALE + LocalButtonScale) + 2.f, 0));
	this->addChild(Left);
	this->addChild(Right);
	ui::Button* Shoot = ui::Button::create("images/Buttons/Shoot_Normal.png", "images/Buttons/Shoot_Selected.png", "images/Buttons/Shoot_Normal.png");
	Shoot->addClickEventListener([&](Ref* sender) {
		Director::getInstance()->replaceScene(MenuScene::createScene());
		});
	Shoot->setScale(GLOBALSCALE + LocalButtonScale);
	Shoot->setPosition(Vec2(x + VISIBLESIZE.width - Right->getContentSize().width * (GLOBALSCALE + LocalButtonScale) / 2.f, y));
	this->addChild(Shoot);
}

GameScene::GameScene() :
	SCREENSIZE(Director::getInstance()->getOpenGLView()->getFrameSize()),
	VISIBLESIZE(Director::getInstance()->getVisibleSize()),
	ORIGIN(Director::getInstance()->getVisibleOrigin()),
	GLOBALSCALE(SCREENSIZE.width / 1280.f),
	Player(Node::create())
{
}

cocos2d::Scene* GameScene::createScene()
{
	return GameScene::create();
}
