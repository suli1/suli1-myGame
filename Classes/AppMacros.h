#ifndef _APP_MACROS_H_
#define _APP_MACROS_H_

#include "cocos2d.h"


#define DESIGN_RESOLUTION_480x320	0
#define DESIGN_RESOLUTION_288X512	1
#define DESIGN_RESOLUTION_960X540	2


#define  TARGET_DESIGN_RESOLUTION_SIZE	DESIGN_RESOLUTION_288X512	

typedef struct tagResource {
	cocos2d::Size size;
	char director[128];
}Resource;

static Resource birdResource = {cocos2d::Size(1080, 1920), "FlappyBird" };
static Resource planeResource = {cocos2d::Size(480, 852), "AirPlane" };


#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_480x320)
static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_288X512)
static cocos2d::Size designResolutionSize = cocos2d::Size(288, 512);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_960X540)
static cocos2d::Size designResolutionSize = cocos2d::Size(960, 540);
#else
#error unknow target design resolution
#endif



#endif // end _APP_MACROS_H_