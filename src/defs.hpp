#ifdef GEODE_IS_WINDOWS
    #ifdef COSMETICS_EXPORTING
        #define COSMETICS_DLL __declspec(dllexport)
    #else
        #define COSMETICS_DLL __declspec(dllimport)
    #endif
#else
    #define COSMETICS_DLL
#endif

#include <Geode/loader/GameEvent.hpp>
// thx prev :3

#define $on_game(type) \
template<class> void GEODE_CONCAT(geodeExecFunction, __LINE__)(geode::GameEvent*); \
namespace { struct GEODE_CONCAT(ExecFuncUnique, __LINE__) {}; } \
static inline auto GEODE_CONCAT(Exec, __LINE__) = (new geode::EventListener( \
    &GEODE_CONCAT(geodeExecFunction, __LINE__)<GEODE_CONCAT(ExecFuncUnique, __LINE__)>, \
    geode::GameEventFilter(geode::GameEventType::type) \
), 0); \
template<class> void GEODE_CONCAT(geodeExecFunction, __LINE__)(geode::GameEvent*)