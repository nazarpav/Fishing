#include "MenuScene.h"
USING_NS_CC;

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
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	ui::Button* button = ui::Button::create("images/ButtonNormal.jpg", "images/ButtonSelected.jpg", "images/ButtonDisabled.jpg");
	if (button == nullptr)
	{
		Utils::problemLoading("'fonts/Marker Felt.ttf'");
		return false;
	}
	else
	{
		//button->setScale(4.f);
		button->setContentSize(Size(250,50));
		float x = visibleSize.width / 2;
		float y = visibleSize.height / 2;
		button->setPosition(Vec2(x, y));
		button->setTitleText("Start Game");
		button->setTitleFontSize(12.f);
		button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				Director::getInstance()->replaceScene(HelloWorld::createScene());
				break;
			default:
				break;
			}
			});

		this->addChild(button);
	}
	return true;
}

void MenuScene::gameCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();
	/*To navigate back to native iOS screen(if present) without quitting the application
	,do not use Director::getInstance()->end() as given above,instead trigger a custom
	event created in RootViewController.mm as below*/
	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}