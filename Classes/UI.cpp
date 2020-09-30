#include "UI.h"
USING_NS_CC;

GameUI::GameUI(PhysicsBody* player, Scene* scene, std::function<void()> exitGameCallback) :_player(player), _scene(scene), _exitGameCallback(exitGameCallback)
{
	_score = Label::createWithTTF("score: 0", "fonts/5by7.ttf", 16);
	_scene->addChild(_score);
	_score->setPosition(_utils.VISIBLESIZE.width / 2 + _utils.ORIGIN.x, _utils.ORIGIN.y + _score->getContentSize().height);
	_scoreCount = 0;
	/*_myDebug = Label::createWithTTF("score: 0", "fonts/5by7.ttf", 16);
	_scene->addChild(_myDebug);
	_myDebug->setPosition(_utils.VISIBLESIZE.width / 2 + _utils.ORIGIN.x, _utils.ORIGIN.y + _myDebug->getContentSize().height + _score->getContentSize().height);
	_myDebug->setColor(cocos2d::Color3B(200,0,0));*/
}

GameUI::~GameUI()
{
}

void GameUI::init()
{
	const float LocalButtonScale = 0.5f;
	ui::Button* Left = ui::Button::create("images/Buttons/MotionInLeft_Normal.png", "images/Buttons/MotionInLeft_Selected.png", "images/Buttons/MotionInLeft_Normal.png");
	Left->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType e) {
		switch (e)
		{
		case ui::Widget::TouchEventType::BEGAN:
			_player->setVelocity(Vec2(-400, 0));
			break;
		case ui::Widget::TouchEventType::ENDED:
		case ui::Widget::TouchEventType::CANCELED:
			if (_player->getVelocity() == Vec2(-400, 0))
			{
				_player->setVelocity(Vec2(0, 0));
			}
			break;
		default:
			break;
		}
		});
	Left->setScale(_utils.GLOBALSCALE + LocalButtonScale);
	const float x = _utils.ORIGIN.x;
	const float y = _utils.ORIGIN.y + Left->getContentSize().height * (_utils.GLOBALSCALE + LocalButtonScale) / 2.f;
	Left->setPosition(Vec2(x + Left->getContentSize().width * (_utils.GLOBALSCALE + LocalButtonScale) / 2.f, y));
	ui::Button* Right = ui::Button::create("images/Buttons/MotionInLeft_Normal.png", "images/Buttons/MotionInLeft_Selected.png", "images/Buttons/MotionInLeft_Normal.png");
	Right->setFlippedX(true);
	Right->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType  e) {
		switch (e)
		{
		case ui::Widget::TouchEventType::BEGAN:
			_player->setVelocity(Vec2(400, 0));
			break;
		case ui::Widget::TouchEventType::ENDED:
		case ui::Widget::TouchEventType::CANCELED:
			if (_player->getVelocity() == Vec2(400, 0))
			{
				_player->setVelocity(Vec2(0, 0));
			}
			break;
		default:
			break;
		}
		});
	Right->setScale(_utils.GLOBALSCALE + LocalButtonScale);
	Right->setPosition(Left->getPosition() + Vec2(Right->getContentSize().height * (_utils.GLOBALSCALE + LocalButtonScale) + 2.f, 0));
	_scene->addChild(Left);
	_scene->addChild(Right);
	ui::Button* Shoot = ui::Button::create("images/Buttons/Shoot_Normal.png", "images/Buttons/Shoot_Selected.png", "images/Buttons/Shoot_Normal.png");
	Shoot->addClickEventListener([&](Ref* sender) {
		Sprite* shell = Sprite::create("images/Game/MyShell.png");
		shell->setPosition(_player->getNode()->getPosition() + Vec2(0, _player->getNode()->getContentSize().height + 1.f));
		PhysicsBody* body = PhysicsBody::createBox(Size(shell->getContentSize().width * 4, shell->getContentSize().height));
		body->setDynamic(true);
		body->setGravityEnable(false);
		shell->addComponent(body);
		body->setVelocity(Vec2(0, 800));
		body->setContactTestBitmask(0xFFFFFFFF);
		_scene->addChild(shell, 0, 103);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/Shoot.mp3", false, 1.f, 1.f, 1.f);
		//SimpleAudioEngine::getInstance()->playEffect("sounds/Shoot.mp3", false, 1.f, 1.f, 1.f);
		});
	Shoot->setScale(_utils.GLOBALSCALE + LocalButtonScale*2);
	Shoot->setPosition(Vec2(x + _utils.VISIBLESIZE.width - Right->getContentSize().width * (_utils.GLOBALSCALE + LocalButtonScale) / 2.f, y));
	_scene->addChild(Shoot);
	ui::Button* CloseGame = ui::Button::create("images/Buttons/Close.png", "images/Buttons/Close.png", "images/Close.png");
	CloseGame->addClickEventListener([&](Ref* sender) {
		if (_exitGameCallback)
		{
			_exitGameCallback();
		}
		});
	CloseGame->setScale(_utils.GLOBALSCALE);
	CloseGame->setPosition(Vec2(x + _utils.VISIBLESIZE.width - CloseGame->getContentSize().width * (_utils.GLOBALSCALE + LocalButtonScale) / 2.f, _utils.VISIBLESIZE.height - CloseGame->getContentSize().height * (_utils.GLOBALSCALE + LocalButtonScale) / 2.f + _utils.ORIGIN.y));
	_scene->addChild(CloseGame);
}

void GameUI::incrementScore()
{
	++_scoreCount;
	_score->setString("score: " + StringUtils::toString(_scoreCount));
}
void GameUI::decrementScore()
{
	--_scoreCount;
	_score->setString("score: " + StringUtils::toString(_scoreCount));
}
//void GameUI::SetMyDebug(std::string val)
//{
//	_myDebug->setString(val.c_str());
//}
