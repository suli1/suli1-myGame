#ifndef _DEFIND_H
#define _DEFIND_H

#define _USE_NS_GAME_FLAPPYBIRD
#define _USE_NS_GAME_AIRPLANE
#define _USE_NS_GAME_TD



#ifdef _USE_NS_GAME_FLAPPYBIRD
    #define NS_FLAPPYBIRD_BEGIN			namespace flappybird {
    #define NS_FLAPPYBIRD_END			}
    #define USING_NS_FLAPPYBIRD			using namespace flappybird
#else
    #define NS_FLAPPYBIRD_BEGIN
    #define NS_FLAPPYBIRD_END
    #define USING_NS_FLAPPYBIRD
#endif


#ifdef _USE_NS_GAME_AIRPLANE
    #define NS_AIRPLANE_BEGIN			namespace airplane {
    #define NS_AIRPLANE_END				}
    #define USING_NS_AIRPLANE			using namespace airplane
#else
    #define NS_AIRPLANE_BEGIN
    #define NS_AIRPLANE_END
    #define USING_NS_AIRPLANE
#endif

#ifdef _USE_NS_GAME_TD
    #define NS_TD_BEGIN                     namespace td {
    #define NS_TD_END                       }
    #define USING_NS_TD                     using namespace td
#else
    #define NS_TD_BEGIN                     namespace td {
    #define NS_TD_END                       }
    #define USING_NS_TD                     using namespace td
#endif



#endif	// end _DEFIND_H