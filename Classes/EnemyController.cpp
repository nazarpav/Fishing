#include "EnemyController.h"
USING_NS_CC;
void EnemyController::ShellContactEnemy(cocos2d::Node* enemy)
{
	enemy->runAction(MoveTo::create(0, Vec2(random(_utils.ORIGIN.x + 64.f, _utils.VISIBLESIZE.width - 64.f), _utils.ORIGIN.y + _utils.VISIBLESIZE.height)));
	enemy->getPhysicsBody()->setVelocity(Vec2(0, -100));
}
void EnemyController::ShellContactPlayer()
{
	_ui.decrementScore();
	Device::vibrate(0.1f);
	if (_ui.playerMakeDamage(10))
	{
		_ui.GameOver();
	}
}
EnemyController::EnemyController(Scene* scene, GameUI& ui) :_scene(scene), _ui(ui)
{
	const int _enemyCountx2 = 2;

	for (size_t i = 0; i < _enemyCountx2; i++)
	{
		EnemyMeteor enemy1 = EnemyMeteor();
		EnemyShip enemy2 = EnemyShip();
		enemy1.setPosition(Vec2(random(_utils.ORIGIN.x + 64.f, _utils.VISIBLESIZE.width - 64.f), _utils.ORIGIN.y + _utils.VISIBLESIZE.height));
		enemy2.setPosition(Vec2(random(_utils.ORIGIN.x + 64.f, _utils.VISIBLESIZE.width - 64.f), _utils.ORIGIN.y + _utils.VISIBLESIZE.height));
		enemy1.setVelocity(Vec2(0, -100));
		enemy2.setVelocity(Vec2(0, -100));
		_scene->addChild(enemy1.getNode(), 0, Tags::Enemy_);
		_scene->addChild(enemy2.getNode(), 0, Tags::Enemy_);
		enemy2.getNode()->runAction(RepeatForever::create(Sequence::create(DelayTime::create(random(1.f, 3.f)), CallFunc::create([&, enemy2]() {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/Shoot.mp3", false, 1.f, 1.f, 1.f);
			Sprite* shell = Sprite::create("images/Game/EnemyShell.png");
			shell->setScale(2.f);
			shell->setPosition(enemy2.getNode()->getPosition() - Vec2(0, enemy2.getNode()->getContentSize().height + 15.f));
			PhysicsBody* body = PhysicsBody::createBox(Size(shell->getContentSize().width , shell->getContentSize().height));
			body->setDynamic(true);
			body->setGravityEnable(false);
			shell->addComponent(body);
			body->setVelocity(Vec2(0, -1000));
			body->setContactTestBitmask(0xFFFFFFFF);
			_scene->addChild(shell, 0, Tags::Shell_);
			}
		), nullptr)));
	}
	//
	_barrierForEnemies = PhysicsBody::createBox(Size(_utils.VISIBLESIZE.width, 10));
	_barrierForEnemies->setCategoryBitmask(BaseEnemy::getCategoryBitmask());
	_barrierForEnemies->setCollisionBitmask(BaseEnemy::getCollisionBitmask());
	_barrierForEnemies->setContactTestBitmask(0xFFFFFFFF);
	_barrierForEnemies->setDynamic(false);
	_barrierForEnemies->setGravityEnable(false);
	Node* barrierNode = Node::create();
	barrierNode->addComponent(_barrierForEnemies);
	barrierNode->setPosition(_utils.ORIGIN.x + _utils.VISIBLESIZE.width / 2, _utils.ORIGIN.y);
	_scene->addChild(barrierNode, 0, Tags::Barrier_);
	//
	_barrierForEnemies = PhysicsBody::createBox(Size(_utils.VISIBLESIZE.width, 10));
	_barrierForEnemies->setCategoryBitmask(BaseEnemy::getCategoryBitmask());
	_barrierForEnemies->setCollisionBitmask(BaseEnemy::getCollisionBitmask());
	_barrierForEnemies->setContactTestBitmask(0xFFFFFFFF);
	_barrierForEnemies->setDynamic(false);
	_barrierForEnemies->setGravityEnable(false);
	barrierNode = Node::create();
	barrierNode->addComponent(_barrierForEnemies);
	barrierNode->setPosition(_utils.ORIGIN.x + _utils.VISIBLESIZE.width / 2, _utils.ORIGIN.y + _utils.VISIBLESIZE.height + 64 * _utils.GLOBALSCALE);
	_scene->addChild(barrierNode, 0, Tags::Barrier_);
	//
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactPostSolve = CC_CALLBACK_1(EnemyController::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, barrierNode);
	//
	_framesVector.reserve(5);
	_framesVector.pushBack(SpriteFrame::create("images/Game/ExplosionAnimation/_1.png", Rect(0, 0, 30, 30)));
	_framesVector.pushBack(SpriteFrame::create("images/Game/ExplosionAnimation/_2.png", Rect(0, 0, 30, 30)));
	_framesVector.pushBack(SpriteFrame::create("images/Game/ExplosionAnimation/_3.png", Rect(0, 0, 30, 30)));
	_framesVector.pushBack(SpriteFrame::create("images/Game/ExplosionAnimation/_4.png", Rect(0, 0, 30, 30)));
	_framesVector.pushBack(SpriteFrame::create("images/Game/ExplosionAnimation/_5.png", Rect(0, 0, 30, 30)));
	_framesVector.pushBack(SpriteFrame::create("images/Game/ExplosionAnimation/_6.png", Rect(0, 0, 30, 30)));
	//_explosionAnimation = Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f));
	_scene->runAction(RepeatForever::create(Sequence::create(DelayTime::create(5.f), CallFunc::create([&]() {
		Bonus bonus = Bonus(BonusType::FirstAidKit, Vec2(random(_utils.ORIGIN.x + 64.f, _utils.VISIBLESIZE.width - 64.f), _utils.ORIGIN.y + _utils.VISIBLESIZE.height));
		_scene->addChild(bonus.getNode(), 1, BonusType::FirstAidKit);
		bonus.getNode()->getPhysicsBody()->setVelocity(Vec2(0, -100));
		}
	), nullptr)));
}

bool EnemyController::onContactBegin(PhysicsContact& contact)
{
	/*static double maxValue = 0;
	std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();*/
	Node* nodeA = contact.getShapeA()->getBody()->getNode();
	Node* nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA == NULL)
	{
		if (nodeB->getTag() == Tags::Enemy_)
		{
			ShellContactEnemy(nodeB);
		}
		return false;
	}
	if (nodeB == NULL)
	{
		if (nodeA->getTag() == Tags::Enemy_)
		{
			ShellContactEnemy(nodeA);
		}
		return false;
	}
	if ((nodeA->getTag() == Tags::Enemy_ && nodeB->getTag() == Tags::Enemy_) || (nodeA->getTag() == Tags::Shell_ && nodeB->getTag() == Tags::Shell_))
	{
		return true;
	}
	if (nodeA->getTag() == Tags::Shell_ || nodeB->getTag() == Tags::Shell_)
	{
		Node* node;
		Node* shell;
		if (nodeA->getTag() == Tags::Shell_)
		{
			shell = nodeA;
			node = nodeB;
		}
		else
		{
			shell = nodeB;
			node = nodeA;
		}
		Sprite* _explosion = Sprite::create();
		_scene->addChild(_explosion);
		_explosion->setScale(2.f);
		_explosion->setPosition(shell->getPosition());
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/explosion_2.mp3", false, 1.f, 1.f, 1.f);
		_explosion->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(_framesVector, 0.05f)), RemoveSelf::create(), nullptr));
		switch (node->getTag())
		{
		case Tags::Player_:
			ShellContactPlayer();
			break;
			//case Tags::Barrier_:
			//	_ui.decrementScore();
			//	_ui.decrementScore();
			//	if (_ui.earthMakeDamage(2))
			//	{
			//		_ui.GameOver();
			//	}
			//	break;
		case Tags::Enemy_:
			ShellContactEnemy(node);
			_ui.incrementScore();
			break;
		case Tags::FirstAidKit_:
			node->removeFromParent();
			break;
		case Tags::AmmoChest_:
			node->removeFromParent();
			break;
		}
		shell->removeFromParent();
	}
	else if ((nodeA->getTag() == Tags::Barrier_ || nodeB->getTag() == Tags::Barrier_) && nodeA->getTag() != Tags::Player_ && nodeB->getTag() != Tags::Player_)
	{
		Node* node;
		Node* barrier;
		if (nodeA->getTag() == Tags::Barrier_)
		{
			barrier = nodeA;
			node = nodeB;
		}
		else
		{
			barrier = nodeB;
			node = nodeA;
		}
		Sprite* _explosion = Sprite::create();
		_scene->addChild(_explosion);
		_explosion->setScale(2.f);
		_explosion->setPosition(barrier->getPosition());
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/explosion_2.mp3", false, 1.f, 1.f, 1.f);
		_explosion->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(_framesVector, 0.05f)), RemoveSelf::create(), nullptr));
		switch (node->getTag())
		{
		case Tags::Enemy_:
			_ui.earthMakeDamage(5);
			_ui.decrementScore();
			ShellContactEnemy(node);
			break;
		case Tags::FirstAidKit_:
			node->removeFromParent();
			break;
		case Tags::AmmoChest_:
			node->removeFromParent();
			break;
		}
	}
	else if (nodeA->getTag() == Tags::Player_ || nodeB->getTag() == Tags::Player_ && nodeA->getTag() != Tags::Barrier_ && nodeB->getTag() != Tags::Barrier_)
	{
		Node* node;
		Node* player;
		if (nodeA->getTag() == Tags::Player_)
		{
			player = nodeA;
			node = nodeB;
		}
		else
		{
			player = nodeB;
			node = nodeA;
		}
		if (node->getTag() == Tags::Barrier_)
		{
			return true;
		}
		Sprite* _explosion = Sprite::create();
		switch (node->getTag())
		{
		case Tags::Enemy_:
			_scene->addChild(_explosion);
			_explosion->setScale(2.f);
			_explosion->setPosition(node->getPosition());
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/explosion_2.mp3", false, 1.f, 1.f, 1.f);
			_explosion->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(_framesVector, 0.05f)), RemoveSelf::create(), nullptr));
			ShellContactPlayer();
			ShellContactEnemy(node);
			break;
		case Tags::FirstAidKit_:
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/useMedChest.mp3", false, 1.f, 1.f, 1.f);
			_ui.equipFirstAidKit();
			node->removeFromParent();
			break;
		case Tags::AmmoChest_:
			node->removeFromParent();
			break;
		}
	}
	/*std::chrono::steady_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	if (maxValue < duration.count() && duration.count() < 0.001)
	{
		maxValue = duration.count();
		_ui->SetMyDebug(StringUtils::toString(duration.count()));
	}*/
	return true;
}
EnemyController::~EnemyController()
{
}

