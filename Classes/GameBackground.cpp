#include "GameBackground.h"
USING_NS_CC;
void GameBackground::InitMapWalls()
{
	_mapWallLeftSprite = Sprite::create("images/Block.png");
	_mapWallLeftSprite->setPosition(_utils.ORIGIN.x + _mapWallLeftSprite->getContentSize().width * _utils.GLOBALSCALE / 2, _utils.ORIGIN.y + _mapWallLeftSprite->getContentSize().height * _utils.GLOBALSCALE);
	_mapWallLeftSprite->setScale(_utils.GLOBALSCALE);
	Texture2D::TexParams params;
	params.minFilter = backend::SamplerFilter::NEAREST;
	params.magFilter = backend::SamplerFilter::NEAREST;
	params.sAddressMode = backend::SamplerAddressMode::REPEAT;
	params.tAddressMode = backend::SamplerAddressMode::REPEAT;
	_mapWallLeftSprite->getTexture()->setTexParameters(params);
	_mapWallLeftSprite->setTextureRect(cocos2d::Rect(0, 0, _mapWallLeftSprite->getContentSize().width * _utils.GLOBALSCALE, _utils.VISIBLESIZE.width));
	PhysicsBody* WallBody = PhysicsBody::createBox(Size(_mapWallLeftSprite->getContentSize().width * _utils.GLOBALSCALE, _utils.VISIBLESIZE.width));
	WallBody->setDynamic(false);
	WallBody->setGravityEnable(false);
	_mapWallLeftSprite->addComponent(WallBody);
	_mapWallRightSprite = Sprite::create("images/Block.png");
	_mapWallRightSprite->setPosition(_utils.ORIGIN.x + _utils.VISIBLESIZE.width - _mapWallRightSprite->getContentSize().width * _utils.GLOBALSCALE / 2, _utils.ORIGIN.y + _mapWallRightSprite->getContentSize().height * _utils.GLOBALSCALE);
	_mapWallRightSprite->setScale(_utils.GLOBALSCALE);
	_mapWallRightSprite->getTexture()->setTexParameters(params);
	_mapWallRightSprite->setTextureRect(cocos2d::Rect(0, 0, _mapWallRightSprite->getContentSize().width * _utils.GLOBALSCALE, _utils.VISIBLESIZE.width));
	WallBody = PhysicsBody::createBox(Size(_mapWallLeftSprite->getContentSize().width * _utils.GLOBALSCALE, _utils.VISIBLESIZE.width));
	WallBody->setDynamic(false);
	WallBody->setGravityEnable(false);
	_mapWallRightSprite->addComponent(WallBody);
}

void GameBackground::InitGameBackground()
{
	_backgroundSprite = Sprite::create("images/Game/GameBackground.png");
	_backgroundSprite->setPosition(0, 0);
	_backgroundSprite->setScale(_utils.GLOBALSCALE);
	Texture2D::TexParams params;
	params.minFilter = backend::SamplerFilter::NEAREST;
	params.magFilter = backend::SamplerFilter::NEAREST;
	params.sAddressMode = backend::SamplerAddressMode::REPEAT;
	params.tAddressMode = backend::SamplerAddressMode::REPEAT;
	_backgroundSprite->getTexture()->setTexParameters(params);
	_backgroundSprite->setTextureRect(cocos2d::Rect(0, 0, _utils.VISIBLESIZE.height, _utils.VISIBLESIZE.width));
}

void GameBackground::UpdateGameBackground(const float dt)
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
	_backgroundSprite->setTextureRect(cocos2d::Rect(tx, ty, _utils.SCREENSIZE.width, _utils.SCREENSIZE.height));
}

void GameBackground::Schedule()
{
	cocos2d::Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(GameBackground::UpdateGameBackground, this), this, 0, false, GameSchedulerKey);
}

void GameBackground::Unschedule()
{
	cocos2d::Director::getInstance()->getScheduler()->unschedule(GameSchedulerKey, this);
}

void GameBackground::init(Scene* scene)
{
	scene->addChild(_backgroundSprite, -1);
	scene->addChild(_mapWallLeftSprite, -1);
	scene->addChild(_mapWallRightSprite, -1);
}

GameBackground::GameBackground()
{
	InitGameBackground();
	InitMapWalls();
	Schedule();
}

GameBackground::~GameBackground()
{
	Unschedule();
}
