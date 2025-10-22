#pragma once
#include "framework.h"

namespace Looting
{
    struct FItemAndCount
    {
        int32 Count;
        UEAllocatedString Name;
        UFortItemDefinition* ItemDefinition;

        FItemAndCount(int32 InCount, UEAllocatedString InName, UFortItemDefinition* InItemDef)
            : Count(InCount), Name(InName), ItemDefinition(InItemDef) {}
    };

    enum class EAmmoType : uint8
    {
        Light,
        Shells,
        Medium,
        Heavy,
        Rockets
    };

    enum class EFortResourceType : uint8
    {
        Wood,
        Stone,
        Metal
    };

    FItemAndCount GetShotguns();
    FItemAndCount GetAssaultRifles();
    FItemAndCount GetSnipers();
    FItemAndCount GetHeals();
    UFortAmmoItemDefinition* GetAmmo(EAmmoType AmmoType);
    UFortResourceItemDefinition* GetResource(EFortResourceType ResourceType);

    void GiveDefaultLoot(AFortPlayerControllerAthena* Controller);
}