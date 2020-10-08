#ifndef PROJ_ANDROID_UI_H
#define PROJ_ANDROID_UI_H
#include "cocos\editor-support\cocostudio\SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Utils.h"
#include "Player.h"
#include "Bonus.h"
class GameUI {
private:
	Utils _utils;
	cocos2d::Scene* _scene;
	cocos2d::Label* _score;
	cocos2d::Sprite* _playerHealthBarBorder;
	cocos2d::ui::LoadingBar* _playerHealthBar;
	cocos2d::Sprite* _earthHealthBarBorder;
	cocos2d::ui::LoadingBar* _earthHealthBar;
	Player _player;
	//cocos2d::Label* _myDebug;
	int _scoreCount;
	std::function<void()> _exitGameCallback;
	void initHealthBar();
public:
	void equipFirstAidKit();
	bool playerMakeDamage(int damage);
	Player& getPlayer();
	bool earthMakeDamage(int damage);
	void GameOver();
	void init();
	void incrementScore();
	void decrementScore();
	//void SetMyDebug(std::string val);
	GameUI(Player& player, cocos2d::Scene* scene, std::function<void()> exitGameCallback);
	~GameUI();
};
#endif //PROJ_ANDROID_UI_H
