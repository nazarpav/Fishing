#include "MenuScene.h"
USING_NS_CC;
MenuScene::MenuScene() :
	SCREENSIZE(Director::getInstance()->getOpenGLView()->getFrameSize()),
	VISIBLESIZE(Director::getInstance()->getVisibleSize()),
	ORIGIN(Director::getInstance()->getVisibleOrigin())
{
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
MenuItemLabel* MenuScene::CreateMenuItem(std::string text, Vec2 position, ccMenuCallback callBack)
{
	const Color3B MenuTextColor = Color3B(30u, 225u, 225u);
	const Color4B MenuTextOutlineColor = Color4B(10u, 10u, 10u, 255u);
	const int MenuOutlineSize = 2;
	MenuItemLabel* MenuItemText = MenuItemLabel::create(Label::createWithTTF(text, "fonts/5by7.ttf", MenuFontSize), callBack);
	MenuItemText->setColor(MenuTextColor);
	MenuItemText->setPosition(position);
	static_cast<Label*>(MenuItemText->getLabel())->enableOutline(MenuTextOutlineColor, MenuOutlineSize);
	return MenuItemText;
}
bool MenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Director::getInstance()->setDisplayStats(false);                    ////Is FPS and other debug information visible
	Vector<MenuItem*> MenuItems;
	MenuItems.pushBack(CreateMenuItem("", Vec2(ORIGIN.x + VISIBLESIZE.width / 2, ORIGIN.y + VISIBLESIZE.height / 2 + MenuFontSize * 3.f), [&](Ref* sender) {}));
	MenuItems.pushBack(CreateMenuItem("Start game", Vec2(ORIGIN.x + VISIBLESIZE.width / 2, ORIGIN.y + VISIBLESIZE.height / 2 + MenuFontSize * 1.5f), [&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::createScene());
		}));
	MenuItems.pushBack(CreateMenuItem("Creators", Vec2(ORIGIN.x + VISIBLESIZE.width / 2, ORIGIN.y + VISIBLESIZE.height / 2 + MenuFontSize / 2.f), [&](Ref* sender) {
		}));
	MenuItems.pushBack(CreateMenuItem("Settings", Vec2(ORIGIN.x + VISIBLESIZE.width / 2, ORIGIN.y + VISIBLESIZE.height / 2 - MenuFontSize / 2.f), [&](Ref* sender) {
		}));
	MenuItems.pushBack(CreateMenuItem("Exit", Vec2(ORIGIN.x + VISIBLESIZE.width / 2, ORIGIN.y + VISIBLESIZE.height / 2 - MenuFontSize * 1.5f), [&](Ref* sender) {
		Director::getInstance()->end();
		}));
	Menu* menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
	MenuBackgroundInit();
	ui::Button* GitHubButton = ui::Button::create("images/GitHubIcon.png", "images/GitHubIcon.png", "images/GitHubIcon.png");
	GitHubButton->addClickEventListener([&](Ref* sender) {
		Application::getInstance()->openURL("https://github.com/nazarpav?tab=repositories");
		});
	const float scale = SCREENSIZE.width / 1280.f;
	GitHubButton->setScale(scale);
	float x = ORIGIN.x + VISIBLESIZE.width - GitHubButton->getContentSize().width * scale / 2.f;
	float y = ORIGIN.y + GitHubButton->getContentSize().height * scale / 2.f;
	GitHubButton->setPosition(Vec2(x, y));
	ui::Button* LinkedInButton = ui::Button::create("images/LinkedInIcon.png", "images/LinkedInIcon.png", "images/LinkedInIcon.png");
	LinkedInButton->addClickEventListener([&](Ref* sender) {
		Application::getInstance()->openURL("https://www.linkedin.com/in/nazar-pavliuk-688435193/");
		});
	LinkedInButton->setScale(scale);
	LinkedInButton->setPosition(Vec2(x - LinkedInButton->getContentSize().width * scale - 2.f * scale, y));
	this->addChild(LinkedInButton, 1);
	this->addChild(GitHubButton, 1);
	return true;
}

void MenuScene::Schedule()
{
	cocos2d::Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(MenuScene::UpdateMenuBackground, this), this, 1.0f / 60, false, MenuSchedulerKey);
}

void MenuScene::Unschedule()
{
	cocos2d::Director::getInstance()->getScheduler()->unschedule(MenuSchedulerKey, this);
}

void MenuScene::UpdateMenuBackground(const float dt)
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
	_backgroundImage->setTextureRect(cocos2d::Rect(tx, ty, SCREENSIZE.width, SCREENSIZE.height));
}

void MenuScene::MenuBackgroundInit()
{
	_backgroundImage = Sprite::create("images/Background_5.png");
	_backgroundImage->setPosition(0, 0);
	Texture2D::TexParams params;
	params.minFilter = backend::SamplerFilter::NEAREST;
	params.magFilter = backend::SamplerFilter::NEAREST;
	params.sAddressMode = backend::SamplerAddressMode::REPEAT;
	params.tAddressMode = backend::SamplerAddressMode::REPEAT;
	_backgroundImage->getTexture()->setTexParameters(params);
	_backgroundImage->setTextureRect(cocos2d::Rect(0, 0, VISIBLESIZE.height, VISIBLESIZE.width));
	this->addChild(_backgroundImage, -1);
}


