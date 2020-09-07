#ifndef PROJ_ANDROID_UTILS_H
#define PROJ_ANDROID_UTILS_H
#include "cocos2d.h"
class Utils
{
public:
	void problemLoading(const char* filename)const;
	const cocos2d::Size SCREENSIZE;
	const cocos2d::Size VISIBLESIZE;
	const cocos2d::Vec2 ORIGIN;
	const float GLOBALSCALE;
	Utils();
};

#endif //PROJ_ANDROID_UTILS_H
