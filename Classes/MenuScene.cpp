#include "MenuScene.h"
#include<CCDirector.h>
USING_NS_CC;
MenuScene::MenuScene()
{
	screenSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	Schedule();
}
MenuScene::~MenuScene()
{
	Unschedule();
}
Scene* MenuScene::createScene()
{
	return MenuScene::create();
}
bool MenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//Director::getInstance()->setDisplayStats(false);                    ////Is FPS and other debug information visible
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vector<MenuItem*> MenuItems;

	Dl = Label::createWithSystemFont("_", "Consolas", 32);
	Dl->setPosition(200, 250);
	_point = Sprite::create("images/point.png");
	_point->setScale(2);
	this->addChild(_point);
	this->addChild(Dl);

	MenuItems.pushBack(MenuItemFont::create(StringUtils::toString(screenSize.width) + " : " + StringUtils::toString(screenSize.height),
		[&](Ref* sender)
		{
			_point->setPosition(_point->getPosition().x - 10, _point->getPosition().y);
			Dl->setString("Coord : x= " + StringUtils::toString(_point->getPosition().x) + " | y= " + StringUtils::toString(_point->getPosition().y));
			//Director::getInstance()->replaceScene(HelloWorld::createScene());
		}));
	MenuItems.back()->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 30.f);
	MenuItems.pushBack(MenuItemFont::create("Game Creators",
		[&](Ref* sender)
		{
			_point->setPosition(_point->getPosition().x + 10, _point->getPosition().y);
			Dl->setString("Coord : x= " + StringUtils::toString(_point->getPosition().x) + " | y= " + StringUtils::toString(_point->getPosition().y));
			//Director::getInstance()->replaceScene(TransitionFade::create(0.5f, HelloWorld::createScene()));
		}));
	MenuItems.back()->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	MenuItems.pushBack(MenuItemFont::create("Exit Game",
		[&](Ref* sender)
		{
			_point->setPosition(_point->getPosition().x, _point->getPosition().y + 10);
			Dl->setString("Coord : x= " + StringUtils::toString(_point->getPosition().x) + " | y= " + StringUtils::toString(_point->getPosition().y));
		}));
	MenuItems.back()->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 30.f);
	MenuItems.pushBack(MenuItemFont::create("Exit Game",
		[&](Ref* sender)
		{
			//Director::getInstance()->end();
			_point->setPosition(_point->getPosition().x, _point->getPosition().y - 10);
			Dl->setString("Coord : x= " + StringUtils::toString(_point->getPosition().x) + " | y= " + StringUtils::toString(_point->getPosition().y));
		}));
	MenuItems.back()->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 60.f);
	Menu* menu = Menu::createWithArray(MenuItems);
	menu->setPosition(0, 0);
	this->addChild(menu, 1);
	BackgroundImagesInit();


	_point->setPosition(10.f, 10.f + origin.y);

	return true;
}

void MenuScene::GameCloseCallback(Ref* pSender)const
{
	Director::getInstance()->end();
}
void MenuScene::GameStartCallback(Ref* sender)const
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void MenuScene::Schedule()
{
	cocos2d::Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(MenuScene::Update, this), this, 1.0f / 60, false, "menuScheduler");
}

void MenuScene::Unschedule()
{
	cocos2d::Director::getInstance()->getScheduler()->unschedule("menuScheduler", this);
}

void MenuScene::Update(const float dt)
{
	if (_backgroundImage == NULL || _backgroundImage == nullptr)
	{
		return;
	}
	static float t = 0.0f;
	t += dt;
	const auto tx = 100 * cosf(t / 10);
	const auto ty = 100 * sinf(t / 10);
	Size visibleSize = Director::getInstance()->getWinSize();
	_backgroundImage->setTextureRect(cocos2d::Rect(tx, ty, screenSize.width, screenSize.height));
}

void MenuScene::BackgroundImagesInit()
{
	Size visibleSize = Director::getInstance()->getWinSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_backgroundImage = Sprite::create("images/bg.png");
	_backgroundImage->setPosition(0, 0);
	Texture2D::TexParams params;
	params.minFilter = backend::SamplerFilter::NEAREST;
	params.magFilter = backend::SamplerFilter::NEAREST;
	params.sAddressMode = backend::SamplerAddressMode::REPEAT;
	params.tAddressMode = backend::SamplerAddressMode::REPEAT;
	_backgroundImage->getTexture()->setTexParameters(params);
	_backgroundImage->setTextureRect(cocos2d::Rect(0, 0, screenSize.width, screenSize.height));
	this->addChild(_backgroundImage, -1);
}

void MenuScene::BackgroundImagesRelease()const
{
}


