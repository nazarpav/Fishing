#include "MenuScene.h"
#include "DebugUtils.h"

inline void DebugUtils::problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
