#ifndef _DEFIND_H
#define _DEFIND_H

#define _USE_NS_GAME_FLAPPYBIRD
#ifdef _USE_NS_GAME_FLAPPYBIRD
	#define NS_FLAPPYBIRD_BEGIN			namespace flappybird {
	#define NS_FLAPPYBIRD_END			}
	#define USING_NS_FLAPPYBIRD			using namespace flappybird
#else
	#define NS_FLAPPYBIRD_BEGIN
	#define NS_FLAPPYBIRD_END
	#define USING_NS_FLAPPYBIRD
#endif


#define NS_AIRPLANE_BEGIN			namespace airplane {
#define NS_AIRPLANE_END				}
#define USING_NS_AIRPLANE			using namespace airplane


#endif	// end _DEFIND_H