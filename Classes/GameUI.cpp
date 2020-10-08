#include "GameUI.h"
USING_NS_CC;

GameUI::GameUI(Player& player, Scene* scene, std::function<void()> exitGameCallback) :_player(player), _scene(scene), _exitGameCallback(exitGameCallback)
{
	_score = Label::createWithTTF("score: 0", "fonts/5by7.ttf", 16);
	_scene->addChild(_score);
	_score->setPosition(_utils.VISIBLESIZE.width / 2 + _utils.ORIGIN.x, _utils.ORIGIN.y + _score->getContentSize().height);
	_scoreCount = 0;
	/*_myDebug = Label::createWithTTF("score: 0", "fonts/5by7.ttf", 16);
	_scene->addChild(_myDebug);
	_myDebug->setPosition(_utils.VISIBLESIZE.width / 2 + _utils.ORIGIN.x, _utils.ORIGIN.y + _myDebug->getContentSize().height + _score->getContentSize().height);
	_myDebug->setColor(cocos2d::Color3B(200,0,0));*/
	initHealthBar();
}

void GameUI::initHealthBar()
{
	_playerHealthBar = ui::LoadingBar::create("images/Game/playerHealthBar.png");
	_scene->addChild(_playerHealthBar);
	_playerHealthBar->setPosition(Vec2(_utils.ORIGIN.x + (16 * _utils.GLOBALSCALE) * _utils.GLOBALSCALE, _utils.ORIGIN.y + _utils.VISIBLESIZE.height * _utils.GLOBALSCALE / 2));
	_playerHealthBar->setScale(_utils.GLOBALSCALE);
	_playerHealthBar->setDirection(ui::LoadingBar::Direction::LEFT);
	_playerHealthBar->setRotation(90.f);
	_playerHealthBar->setPercent(100);
	_playerHealthBarBorder = Sprite::create("images/Game/playerHealthBarBorder.png");
	_scene->addChild(_playerHealthBarBorder);
	_playerHealthBarBorder->setPosition(_playerHealthBar->getPosition());
	_playerHealthBarBorder->setRotation(90.f);

	_playerHealthBar->setFlippedX(true);
	_playerHealthBarBorder->setFlippedX(true);
	_earthHealthBar = ui::LoadingBar::create("images/Game/earthHealthBar.png");
	_scene->addChild(_earthHealthBar);
	_earthHealthBar->setPosition(Vec2(_utils.ORIGIN.x + _utils.VISIBLESIZE.width - (16 * _utils.GLOBALSCALE) * _utils.GLOBALSCALE, _utils.ORIGIN.y + _utils.VISIBLESIZE.height * _utils.GLOBALSCALE / 2));
	_earthHealthBar->setDirection(ui::LoadingBar::Direction::LEFT);
	_earthHealthBar->setScale(_utils.GLOBALSCALE);
	_earthHealthBar->setRotation(90.f);
	_earthHealthBar->setPercent(100);
	_earthHealthBarBorder = Sprite::create("images/Game/playerHealthBarBorder.png");
	_scene->addChild(_earthHealthBarBorder);
	_earthHealthBarBorder->setPosition(_earthHealthBar->getPosition());
	_earthHealthBarBorder->setRotation(90.f);
	_earthHealthBar->setFlippedX(true);
	_earthHealthBarBorder->setFlippedX(true);
	_earthHealthBar->setFlippedY(true);
	_earthHealthBarBorder->setFlippedY(true);
}

GameUI::~GameUI()
{
}

void GameUI::equipFirstAidKit()
{
	Bonus::Action(_player, BonusType::FirstAidKit);
	_playerHealthBar->setPercent(_player.getHealthCount());
}

bool GameUI::playerMakeDamage(int damage)
{
	_playerHealthBar->setPercent(_player.makeDamage(damage));
	if (_playerHealthBar->getPercent() <= 0)
	{
		return true;
	}
	return false;
}
Player& GameUI::getPlayer()
{
	return _player;
}
bool GameUI::earthMakeDamage(int damage)
{
	_earthHealthBar->setPercent(_earthHealthBar->getPercent() - damage / 3);
	if (_earthHealthBar->getPercent() <= 0)
	{
		return true;
	}
	return false;
}

void GameUI::GameOver()
{
	_exitGameCallback();
}

void GameUI::init()
{
	const float LocalButtonScale = 0.6f;
	ui::Button* Left = ui::Button::create("images/Buttons/MotionInLeft_Normal.png", "images/Buttons/MotionInLeft_Selected.png", "images/Buttons/MotionInLeft_Normal.png");
	Left->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType e) {
		switch (e)
		{
		case ui::Widget::TouchEventType::BEGAN:
			_player.getPhysicsBody()->setVelocity(Vec2(-400, 0));
			break;
		case ui::Widget::TouchEventType::ENDED:
		case ui::Widget::TouchEventType::CANCELED:
			if (_player.getPhysicsBody()->getVelocity() == Vec2(-400, 0))
			{
				_player.getPhysicsBody()->setVelocity(Vec2(0, 0));
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
			_player.getPhysicsBody()->setVelocity(Vec2(400, 0));
			break;
		case ui::Widget::TouchEventType::ENDED:
		case ui::Widget::TouchEventType::CANCELED:
			if (_player.getPhysicsBody()->getVelocity() == Vec2(400, 0))
			{
				_player.getPhysicsBody()->setVelocity(Vec2(0, 0));
			}
			break;
		default:
			break;
		}
		});
	Right->setScale(_utils.GLOBALSCALE + LocalButtonScale);
	Right->setPosition(Left->getPosition() + Vec2(Right->getContentSize().height * (_utils.GLOBALSCALE + LocalButtonScale) + 2.f, 0));
	_scene->addChild(Left, 15);
	_scene->addChild(Right, 15);
	ui::Button* Shoot = ui::Button::create("images/Buttons/Shoot_Normal.png", "images/Buttons/Shoot_Selected.png", "images/Buttons/Shoot_Normal.png");
	Shoot->addClickEventListener([&](Ref* sender) {
		Sprite* shell = Sprite::create("images/Game/MyShell.png");
		shell->setPosition(_player.getNode()->getPosition() + Vec2(0, _player.getNode()->getContentSize().height + 5.f));
		shell->setScale(2.f * _utils.GLOBALSCALE);
		PhysicsBody* body = PhysicsBody::createBox(Size(shell->getContentSize().width * 4, shell->getContentSize().height));
		body->setDynamic(true);
		body->setGravityEnable(false);
		shell->addComponent(body);
		body->setVelocity(Vec2(0, 1000));
		body->setContactTestBitmask(0xFFFFFFFF);
		_scene->addChild(shell, 0, 103);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/Shoot.mp3", false, 1.f, 1.f, 1.f);
		});
	Shoot->setScale(_utils.GLOBALSCALE + LocalButtonScale);
	Shoot->setPosition(Vec2(x + _utils.VISIBLESIZE.width - Right->getContentSize().width * (_utils.GLOBALSCALE + LocalButtonScale) / 2.f, y));
	_scene->addChild(Shoot,15);
	ui::Button* CloseGame = ui::Button::create("images/Buttons/Close.png", "images/Buttons/Close.png", "images/Close.png");
	CloseGame->addClickEventListener([&](Ref* sender) {
		if (_exitGameCallback)
		{
			GameOver();
		}
		});
	CloseGame->setPosition(Vec2(x + _utils.VISIBLESIZE.width - CloseGame->getContentSize().width * (_utils.GLOBALSCALE + LocalButtonScale) / 2.f, _utils.VISIBLESIZE.height - CloseGame->getContentSize().height * (_utils.GLOBALSCALE + LocalButtonScale) / 2.f + _utils.ORIGIN.y));
	CloseGame->setScale(_utils.GLOBALSCALE + LocalButtonScale/2);
	_scene->addChild(CloseGame, 15);
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
