#ifdef GEODE_IS_WINDOWS
    #ifdef COSMETICS_EXPORTING
        #define COSMETICS_DLL __declspec(dllexport)
    #else
        #define COSMETICS_DLL __declspec(dllimport)
    #endif
#else
    #define COSMETICS_DLL
#endif