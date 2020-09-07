#include "Utils.h"
USING_NS_CC;
void Utils::problemLoading(const char* filename)const
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
Utils::Utils() :
	SCREENSIZE(Director::getInstance()->getOpenGLView()->getFrameSize()),
	VISIBLESIZE(Director::getInstance()->getVisibleSize()),
	ORIGIN(Director::getInstance()->getVisibleOrigin()),
	GLOBALSCALE(SCREENSIZE.width / 1280.f)
{
}