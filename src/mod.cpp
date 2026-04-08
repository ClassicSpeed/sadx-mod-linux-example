#include <SADXModLoader.h>
extern "C"
{
    __declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
    {
        // Called when the mod initializes.
        // path points to your mod folder.
        (void)path;
        (void)helperFunctions;
    }

    __declspec(dllexport) void __cdecl OnFrame()
    {
        // Simple test: force rings to 999 every frame.
        Rings = 999;
    }

    // Required so Mod Loader recognizes this DLL.
    __declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}
