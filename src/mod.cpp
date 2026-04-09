#include <SADXModLoader.h>
#include <UsercallFunctionHandler.h>


extern "C" {
void HandleHudDisplayRings(signed int ring_count, unsigned char digits, NJS_SPRITE* hud);
UsercallFuncVoid(_hudDisplayRingsHook, (signed int ringCount, unsigned char digits, NJS_SPRITE* hud),
                 (ringCount, digits, hud), 0x425960, rEAX, rBL, rESI);


__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
{
    _hudDisplayRingsHook.Hook(HandleHudDisplayRings);
}

// Simple OnFrame test
__declspec(dllexport) void __cdecl OnFrame()
{
    Rings = 999;
}

// UsercallFuncVoid example
void HandleHudDisplayRings(const signed int ringCount, const unsigned char digits, NJS_SPRITE* hud)
{
    _hudDisplayRingsHook.Original(ringCount, 5, hud);
}

__declspec(dllexport) ModInfo SADXModInfo = {ModLoaderVer};
}
