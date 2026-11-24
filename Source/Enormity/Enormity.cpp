#include "Enormity.h"
#include "Modules/ModuleManager.h"
#include "Misc/Paths.h"
#include "ShaderCore.h"

class FEnormityModule : public FDefaultGameModuleImpl
{
public:
    virtual void StartupModule() override
    {
        // Maps physical "YourProject/Shaders" to virtual "/Project" path
        FString ShaderDir = FPaths::Combine(FPaths::ProjectDir(), TEXT("Shaders"));
        AddShaderSourceDirectoryMapping(TEXT("/Project"), ShaderDir);
    }

    virtual void ShutdownModule() override
    {
        ResetAllShaderSourceDirectoryMappings();
    }
};

IMPLEMENT_PRIMARY_GAME_MODULE( FEnormityModule, Enormity, "Enormity" );