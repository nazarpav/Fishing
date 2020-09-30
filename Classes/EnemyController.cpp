#include "EnemyController.h"
USING_NS_CC;
EnemyController::EnemyController(Scene* scene, GameUI* ui) :_scene(scene), _ui(ui)
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
		_scene->addChild(enemy1.getNode(), 0, 102);
		_scene->addChild(enemy2.getNode(), 0, 102);
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
	_scene->addChild(barrierNode, 0, 101);
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
}

//bool EnemyController::onContactBegin(PhysicsContact& contact)
//{
//	static double maxValue =0 ;
//	std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
//	Node* nodeA = contact.getShapeA()->getBody()->getNode();
//	Node* nodeB = contact.getShapeB()->getBody()->getNode();
//	if (nodeA->getTag() == 102 && nodeB->getTag() == 102)
//	{
//		return true;
//	}
//	/*if (nodeB->getTag() == 103 && nodeA->getTag() != 104 && nodeA->getTag() != 103)
//		nodeB->removeFromParentAndCleanup(true);
//	if (nodeA->getTag() == 103 && nodeB->getTag() != 104 && nodeB->getTag() != 103)
//		nodeA->removeFromParentAndCleanup(true);*/
//	if (nodeA->getTag() == 102)
//	{
//		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/explosion_2.mp3", false, 1.f, 1.f, 1.f);
//		try {
//			nodeA->getChildByTag(1001)->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(_framesVector, 0.1f)), RemoveSelf::create(), nullptr));
//			//nodeA->getChildByTag(1001)->runAction(Animate::create(Animation::createWithSpriteFrames(_framesVector, 0.1f)));
//		}
//		catch (std::string m) {
//			log("%s", m.c_str());
//		}
//		nodeA->runAction(MoveTo::create(0, Vec2(random(_utils.ORIGIN.x + 64.f, _utils.VISIBLESIZE.width - 64.f), _utils.ORIGIN.y + _utils.VISIBLESIZE.height)));
//		nodeA->getPhysicsBody()->setVelocity(Vec2(0, -100));
//		_ui->incrementScore();
//		//return true;
//	}
//	if (nodeB->getTag() == 102)
//	{
//		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/explosion_2.mp3", false, 1.f, 1.f, 1.f);
//		try {
//			//nodeB->getChildByTag(1001)->runAction(Animate::create(Animation::createWithSpriteFrames(_framesVector, 0.1f)));
//			nodeB->getChildByTag(1001)->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(_framesVector, 0.1f)), RemoveSelf::create(), nullptr));
//		}
//		catch (std::string m) {
//			log("%s", m.c_str());
//		}
//		nodeB->runAction(MoveTo::create(0, Vec2(random(_utils.ORIGIN.x + 64.f, _utils.VISIBLESIZE.width - 64.f), _utils.ORIGIN.y + _utils.VISIBLESIZE.height)));
//		nodeB->getPhysicsBody()->setVelocity(Vec2(0, -100));
//		_ui->incrementScore();
//		//return true;
//	}
//	//_ui->decrementScore();
//	//nodeB->setPosition(Vec2(random(0.f, _utils.VISIBLESIZE.width) + _utils.ORIGIN.x, _utils.ORIGIN.y + _utils.VISIBLESIZE.height));
//	//nodeB->removeFromParentAndCleanup(true);
//	std::chrono::steady_clock::time_point end = std::chrono::high_resolution_clock::now();
//	std::chrono::duration<double> duration = end - start;
//	if (maxValue < duration.count()&& duration.count()<0.001)
//	{
//		maxValue = duration.count();
//		_ui->SetMyDebug(StringUtils::toString(duration.count()));
//	}
//	return true;
//}
bool EnemyController::onContactBegin(PhysicsContact& contact)
{
	/*static double maxValue = 0;
	std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();*/
	Node* nodeA = contact.getShapeA()->getBody()->getNode();
	Node* nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA->getTag() == 102 && nodeB->getTag() == 102)
	{
		return true;
	}
	if (nodeA->getTag() != 102 && nodeB->getTag() != 102)
	{
	}
	else
	{
		Node* enemy;
		Node* otherNode;
		if (nodeA->getTag() == 102)
		{
			enemy = nodeA;
			otherNode = nodeB;
		}
		else
		{
			enemy = nodeB;
			otherNode = nodeA;
		}
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/explosion_2.mp3", false, 1.f, 1.f, 1.f);
		Sprite* _explosion = Sprite::create();
		_scene->addChild(_explosion);
		_explosion->setScale(2.f);
		_explosion->setPosition(enemy->getPosition());
		_explosion->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(_framesVector, 0.05f)), RemoveSelf::create(),nullptr));
		enemy->runAction(MoveTo::create(0, Vec2(random(_utils.ORIGIN.x + 64.f, _utils.VISIBLESIZE.width - 64.f), _utils.ORIGIN.y + _utils.VISIBLESIZE.height)));
		enemy->getPhysicsBody()->setVelocity(Vec2(0, -100));
		if (otherNode->getTag() == 103)
		{
			otherNode->removeFromParentAndCleanup(true);
			_ui->incrementScore();
		}
		else 
		{
			_ui->decrementScore();
		}
	}
	/*if (nodeB->getTag() == 103 && nodeA->getTag() != 104 && nodeA->getTag() != 103)
		nodeB->removeFromParentAndCleanup(true);
	if (nodeA->getTag() == 103 && nodeB->getTag() != 104 && nodeB->getTag() != 103)
		nodeA->removeFromParentAndCleanup(true);*/
		//if (nodeA->getTag() == 102)
		//{
		//	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/explosion_2.mp3", false, 1.f, 1.f, 1.f);
		//	//try {
		//	//	//nodeA->getChildByTag(1001)->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(_framesVector, 0.1f)), RemoveSelf::create(), nullptr));
		//	//	//nodeA->getChildByTag(1001)->runAction(Animate::create(Animation::createWithSpriteFrames(_framesVector, 0.1f)));
		//	//}
		//	//catch (std::string m) {
		//	//	log("%s", m.c_str());
		//	//}
		//	nodeA->runAction(MoveTo::create(0, Vec2(random(_utils.ORIGIN.x + 64.f, _utils.VISIBLESIZE.width - 64.f), _utils.ORIGIN.y + _utils.VISIBLESIZE.height)));
		//	nodeA->getPhysicsBody()->setVelocity(Vec2(0, -100));
		//	_ui->incrementScore();
		//	//return true;
		//}
		//if (nodeB->getTag() == 102)
		//{
		//	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/explosion_2.mp3", false, 1.f, 1.f, 1.f);
		//	//try {
		//	//	//nodeB->getChildByTag(1001)->runAction(Animate::create(Animation::createWithSpriteFrames(_framesVector, 0.1f)));
		//	//	//nodeB->getChildByTag(1001)->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(_framesVector, 0.1f)), RemoveSelf::create(), nullptr));
		//	//}
		//	//catch (std::string m) {
		//	//	log("%s", m.c_str());
		//	//}
		//	nodeB->runAction(MoveTo::create(0, Vec2(random(_utils.ORIGIN.x + 64.f, _utils.VISIBLESIZE.width - 64.f), _utils.ORIGIN.y + _utils.VISIBLESIZE.height)));
		//	nodeB->getPhysicsBody()->setVelocity(Vec2(0, -100));
		//	_ui->incrementScore();
		//	//return true;
		//}
		//_ui->decrementScore();
		//nodeB->setPosition(Vec2(random(0.f, _utils.VISIBLESIZE.width) + _utils.ORIGIN.x, _utils.ORIGIN.y + _utils.VISIBLESIZE.height));
		//nodeB->removeFromParentAndCleanup(true);
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

