#ifndef PROJ_ANDROID_BONUS_H
#define PROJ_ANDROID_BONUS_H
#include"Player.h"
#include"cocos2d.h"
enum BonusType  {
	FirstAidKit=1101,
	AmmoChest=1102,
	UnknownBonus=1003
};
class Bonus {
private:
	cocos2d::Node* _baseNode;
public:
	Bonus(BonusType bonusType, cocos2d::Vec2 position);
	cocos2d::Node* getNode();
	static void Action(Player& player, BonusType bonus);
};
#endif //PROJ_ANDROID_BONUS_H
