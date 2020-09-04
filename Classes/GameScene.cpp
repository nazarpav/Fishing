#include "GameScene.h"
#include <cocos\editor-support\cocostudio\SimpleAudioEngine.cpp>
USING_NS_CC;

bool GameScene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	InitPlayer();
	InitButtons();
	InitGameBackground();
	InitMapWalls();
	return true;
}

void GameScene::Schedule()
{
	cocos2d::Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(GameScene::UpdateGameBackground, this), this, 0, false, GameSchedulerKey);
}

void GameScene::Unschedule()
{
	cocos2d::Director::getInstance()->getScheduler()->unschedule(GameSchedulerKey, this);
}

void GameScene::ButtonShootCallback(cocos2d::Ref* sender)
{
	UserDefault* def = UserDefault::getInstance();


	Director::getInstance()->replaceScene(MenuScene::createScene());
}

void GameScene::InitPlayer()
{
	Sprite* sprite = Sprite::create("images/Player/PlayerIdle.png");
	Player->setPosition(Vec2(ORIGIN.x+ VISIBLESIZE.width / 2, ORIGIN.y+ VISIBLESIZE.height / 4));
	PlayerBody = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height));
	PlayerBody->setDynamic(true);
	PlayerBody->setGravityEnable(false);
	PlayerBody->setRotationEnable(false);
	Sprite* mySprite = Sprite::create();

	//Vec2 pos = Vec2(VISIBLESIZE.width / 2, VISIBLESIZE.height / 4);

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(4);
	animFrames.pushBack(SpriteFrame::create("images/Player/EngineFireAnimation/_1.png", Rect(0, 0, 30, 30)));
	animFrames.pushBack(SpriteFrame::create("images/Player/EngineFireAnimation/_2.png", Rect(0, 0, 30, 30)));
	animFrames.pushBack(SpriteFrame::create("images/Player/EngineFireAnimation/_3.png", Rect(0, 0, 30, 30)));
	animFrames.pushBack(SpriteFrame::create("images/Player/EngineFireAnimation/_4.png", Rect(0, 0, 30, 30)));

	mySprite->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.2f))));
	//mySprite->setPosition(Vec2(mySprite->getContentSize().width/2,-mySprite->getContentSize().height/2));
	mySprite->setPosition(Point::ZERO);
	sprite->setPosition(Point::ZERO);
	PlayerBody->setPositionOffset(Point::ZERO);

	Player->addComponent(PlayerBody);
	Player->addChild(sprite, 0, "Idle");
	Player->addChild(mySprite, 2);
	//static_cast<Sprite*>(Player->getChildByName("Idle"))->setVisible(false);
	this->addChild(Player);
}

void GameScene::InitMapWalls()
{
	getPhysicsWorld()->setDebugDrawMask(0xffff);
	_mapWallLeftSprite = Sprite::create("images/Block.png");
	_mapWallLeftSprite->setPosition(ORIGIN.x + _mapWallLeftSprite->getContentSize().width * GLOBALSCALE / 2, ORIGIN.y + _mapWallLeftSprite->getContentSize().height * GLOBALSCALE);
	_mapWallLeftSprite->setScale(GLOBALSCALE);
	Texture2D::TexParams params;
	params.minFilter = backend::SamplerFilter::NEAREST;
	params.magFilter = backend::SamplerFilter::NEAREST;
	params.sAddressMode = backend::SamplerAddressMode::REPEAT;
	params.tAddressMode = backend::SamplerAddressMode::REPEAT;
	_mapWallLeftSprite->getTexture()->setTexParameters(params);
	_mapWallLeftSprite->setTextureRect(cocos2d::Rect(0, 0, _mapWallLeftSprite->getContentSize().width * GLOBALSCALE, VISIBLESIZE.width));
	PhysicsBody* WallBody = PhysicsBody::createBox(Size(_mapWallLeftSprite->getContentSize().width * GLOBALSCALE, VISIBLESIZE.width));
	WallBody->setDynamic(false);
	WallBody->setGravityEnable(false);
	_mapWallLeftSprite->addComponent(WallBody);
	this->addChild(_mapWallLeftSprite, -1);
	_mapWallRightSprite = Sprite::create("images/Block.png");
	_mapWallRightSprite->setPosition(ORIGIN.x + VISIBLESIZE.width - _mapWallRightSprite->getContentSize().width * GLOBALSCALE / 2, ORIGIN.y + _mapWallRightSprite->getContentSize().height * GLOBALSCALE);
	_mapWallRightSprite->setScale(GLOBALSCALE);
	_mapWallRightSprite->getTexture()->setTexParameters(params);
	_mapWallRightSprite->setTextureRect(cocos2d::Rect(0, 0, _mapWallRightSprite->getContentSize().width * GLOBALSCALE, VISIBLESIZE.width));
	WallBody = PhysicsBody::createBox(Size(_mapWallLeftSprite->getContentSize().width * GLOBALSCALE, VISIBLESIZE.width));
	WallBody->setDynamic(false);
	WallBody->setGravityEnable(false);
	_mapWallRightSprite->addComponent(WallBody);
	this->addChild(_mapWallRightSprite, -1);
}

void GameScene::InitButtons()
{
	const float LocalButtonScale = 0.5f;
	ui::Button* Left = ui::Button::create("images/Buttons/MotionInLeft_Normal.png", "images/Buttons/MotionInLeft_Selected.png", "images/Buttons/MotionInLeft_Normal.png");
	Left->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType e) {
		switch (e)
		{
		case ui::Widget::TouchEventType::BEGAN:
			PlayerBody->setVelocity(Vec2(-400, 0));
			break;
		case ui::Widget::TouchEventType::ENDED:
		case ui::Widget::TouchEventType::CANCELED:
			if (PlayerBody->getVelocity() == Vec2(-400, 0))
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
			PlayerBody->setVelocity(Vec2(400, 0));
			break;
		case ui::Widget::TouchEventType::ENDED:
		case ui::Widget::TouchEventType::CANCELED:
			if (PlayerBody->getVelocity() == Vec2(400, 0))
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
		Sprite* sprite = Sprite::create("images/Game/MyShell.png");
		sprite->setPosition(Player->getPosition()+Vec2(0, Player->getContentSize().height/2+1));
		PhysicsBody* body = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height));
		body->setDynamic(true);
		body->setGravityEnable(false);
		sprite->addComponent(body);
		body->setVelocity(Vec2(0, 800));
		addChild(sprite);
		SimpleAudioEngine::getInstance()->playEffect("sounds/Shoot.mp3", false, 1.f, 1.f, 1.f);
		});
	Shoot->setScale(GLOBALSCALE + LocalButtonScale);
	Shoot->setPosition(Vec2(x + VISIBLESIZE.width - Right->getContentSize().width * (GLOBALSCALE + LocalButtonScale) / 2.f, y));
	this->addChild(Shoot);
	ui::Button* CloseGame = ui::Button::create("images/Buttons/Close.png", "images/Buttons/Close.png", "images/Close.png");
	CloseGame->addClickEventListener([&](Ref* sender) {
		Director::getInstance()->replaceScene(MenuScene::createScene());
		});
	CloseGame->setScale(GLOBALSCALE);
	CloseGame->setPosition(Vec2(x + VISIBLESIZE.width - CloseGame->getContentSize().width * (GLOBALSCALE + LocalButtonScale) / 2.f, VISIBLESIZE.height - CloseGame->getContentSize().height * (GLOBALSCALE + LocalButtonScale) / 2.f + ORIGIN.y));
	this->addChild(CloseGame);
}

void GameScene::InitShells()
{
}

void GameScene::UpdateGameBackground(const float dt)
{
	if (_backgroundSprite == NULL || _backgroundSprite == nullptr)
	{
		return;
	}
	static float t = 0.0f;
	t += dt;
	const auto tx = 100 * cosf(t / 10);
	const auto ty = 100 * sinf(t / 10);
	Size visibleSize = Director::getInstance()->getWinSize();
	_backgroundSprite->setTextureRect(cocos2d::Rect(tx, ty, SCREENSIZE.width, SCREENSIZE.height));
}

void GameScene::InitGameBackground()
{
	_backgroundSprite = Sprite::create("images/Game/GameBackground.png");
	_backgroundSprite->setPosition(0, 0);
	_backgroundSprite->setScale(GLOBALSCALE);
	Texture2D::TexParams params;
	params.minFilter = backend::SamplerFilter::NEAREST;
	params.magFilter = backend::SamplerFilter::NEAREST;
	params.sAddressMode = backend::SamplerAddressMode::REPEAT;
	params.tAddressMode = backend::SamplerAddressMode::REPEAT;
	_backgroundSprite->getTexture()->setTexParameters(params);
	_backgroundSprite->setTextureRect(cocos2d::Rect(0, 0, VISIBLESIZE.height, VISIBLESIZE.width));
	this->addChild(_backgroundSprite, -1);
}

GameScene::GameScene() :
	SCREENSIZE(Director::getInstance()->getOpenGLView()->getFrameSize()),
	VISIBLESIZE(Director::getInstance()->getVisibleSize()),
	ORIGIN(Director::getInstance()->getVisibleOrigin()),
	GLOBALSCALE(SCREENSIZE.width / 1280.f),
	Player(Node::create())
{
	Schedule();
}

GameScene::~GameScene()
{
	Unschedule();
}

cocos2d::Scene* GameScene::createScene()
{
	return GameScene::create();
}
