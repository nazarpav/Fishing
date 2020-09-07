#include "Player.h"
USING_NS_CC;
void Player::init()
{
	Sprite* sprite = Sprite::create("images/Player/PlayerIdle.png");
	_player->setPosition(Vec2(_utils.ORIGIN.x + _utils.VISIBLESIZE.width / 2, _utils.ORIGIN.y + _utils.VISIBLESIZE.height / 4));
	_playerBody = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height));
	_playerBody->setDynamic(true);
	_playerBody->setGravityEnable(false);
	_playerBody->setRotationEnable(false);
	Sprite* mySprite = Sprite::create();

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(4);
	animFrames.pushBack(SpriteFrame::create("images/Player/EngineFireAnimation/_1.png", Rect(0, 0, 30, 30)));
	animFrames.pushBack(SpriteFrame::create("images/Player/EngineFireAnimation/_2.png", Rect(0, 0, 30, 30)));
	animFrames.pushBack(SpriteFrame::create("images/Player/EngineFireAnimation/_3.png", Rect(0, 0, 30, 30)));
	animFrames.pushBack(SpriteFrame::create("images/Player/EngineFireAnimation/_4.png", Rect(0, 0, 30, 30)));

	mySprite->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.2f))));
	mySprite->setPosition(Point::ZERO);
	sprite->setPosition(Point::ZERO);
	_playerBody->setPositionOffset(Point::ZERO);

	_player->addComponent(_playerBody);
	_player->addChild(sprite, 0, "Idle");
	_player->addChild(mySprite, 2);
}

Player::Player()
{
	_player = Node::create();
	init();
}

Player::~Player()
{
}

Node* Player::getNode()
{
	return _player;
}

cocos2d::PhysicsBody* Player::getPhysicsBody()
{
	return _playerBody;
}
