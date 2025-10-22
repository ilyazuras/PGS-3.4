#include "pch.h"
#include "Looting.h"
#include "Utils.h"
#include "Inventory.h"

FItemAndCount Looting::GetWeapons()
{
 static UEAllocatedVector<FItemAndCount> Weapons{
  FItemAndCount(1,{},Utils::FindObject<UFortWeaponRangedItemDefinition>(L"/Game/Athena/Items/Weapons/WID_Assault_AutoHigh_Athena_R_Ore_T03.WID_Assault_AutoHigh_Athena_R_Ore_T03")),
  FItemAndCount(1,{},Utils::FindObject<UFortWeaponRangedItemDefinition>(L"/Game/Athena/Items/Weapons/WID_Shotgun_Standard_Athena_R_Ore_T03.WID_Shotgun_Standard_Athena_R_Ore_T03")),
  FItemAndCount(1,{},Utils::FindObject<UFortWeaponRangedItemDefinition>(L"/Game/Athena/Items/Weapons/WID_Sniper_BoltAction_Scope_Athena_R_Ore_T03.WID_Sniper_BoltAction_Scope_Athena_R_Ore_T03")),
  FItemAndCount(1,{},Utils::FindObject<UFortWeaponRangedItemDefinition>(L"/Game/Athena/Items/Weapons/WID_Pistol_SemiAuto_Athena_R_Ore_T03.WID_Pistol_SemiAuto_Athena_R_Ore_T03"))
 };
 return Weapons[rand()%(Weapons.size()-1)];
}

FItemAndCount Looting::GetConsumables()
{
 static UEAllocatedVector<FItemAndCount> Consumables{
  FItemAndCount(3,{},Utils::FindObject<UFortConsumableItemDefinition>(L"/Game/Athena/Items/Consumables/Athena_Shields.Athena_Shields")),
  FItemAndCount(6,{},Utils::FindObject<UFortConsumableItemDefinition>(L"/Game/Athena/Items/Consumables/Athena_ShieldSmall.Athena_ShieldSmall")),
  FItemAndCount(3,{},Utils::FindObject<UFortConsumableItemDefinition>(L"/Game/Athena/Items/Consumables/Athena_Bandage.Athena_Bandage")),
  FItemAndCount(2,{},Utils::FindObject<UFortConsumableItemDefinition>(L"/Game/Athena/Items/Consumables/Athena_Medkit.Athena_Medkit"))
 };
 return Consumables[rand()%(Consumables.size()-1)];
}

UFortAmmoItemDefinition* Looting::GetAmmo(EAmmoType AmmoType)
{
 static UEAllocatedVector<UFortAmmoItemDefinition*> Ammos{
  Utils::FindObject<UFortAmmoItemDefinition>(L"/Game/Athena/Items/Ammo/AthenaAmmoDataBulletsLight.AthenaAmmoDataBulletsLight"),
  Utils::FindObject<UFortAmmoItemDefinition>(L"/Game/Athena/Items/Ammo/AthenaAmmoDataShells.AthenaAmmoDataShells"),
  Utils::FindObject<UFortAmmoItemDefinition>(L"/Game/Athena/Items/Ammo/AthenaAmmoDataBulletsMedium.AthenaAmmoDataBulletsMedium"),
  Utils::FindObject<UFortAmmoItemDefinition>(L"/Game/Athena/Items/Ammo/AthenaAmmoDataBulletsHeavy.AthenaAmmoDataBulletsHeavy"),
  Utils::FindObject<UFortAmmoItemDefinition>(L"/Game/Athena/Items/Ammo/AmmoDataRockets.AmmoDataRockets")
 };
 return Ammos[(uint8)AmmoType];
}

UFortResourceItemDefinition* Looting::GetResource(EFortResourceType ResourceType)
{
 static UEAllocatedVector<UFortResourceItemDefinition*> Resources{
  Utils::FindObject<UFortResourceItemDefinition>(L"/Game/Items/ResourcePickups/WoodItemData.WoodItemData"),
  Utils::FindObject<UFortResourceItemDefinition>(L"/Game/Items/ResourcePickups/StoneItemData.StoneItemData"),
  Utils::FindObject<UFortResourceItemDefinition>(L"/Game/Items/ResourcePickups/MetalItemData.MetalItemData")
 };
 return Resources[(uint8)ResourceType];
}

void Looting::GiveDefaultLoot(AFortPlayerControllerAthena* Controller)
{
 if(!Controller)return;
 Inventory::ClearInventory(Controller);
 auto Weapon=GetWeapons().ItemDefinition;
 Inventory::GiveItem(Controller,Weapon,1,0,1,true,true,0);
 auto Heal=GetConsumables().ItemDefinition;
 Inventory::GiveItem(Controller,Heal,3,0,2,false,true,0);
 Inventory::GiveItem(Controller,(UFortItemDefinition*)GetResource(EFortResourceType::Wood),999,0,3,false,true,0);
 Inventory::GiveItem(Controller,(UFortItemDefinition*)GetResource(EFortResourceType::Stone),999,0,4,false,true,0);
 Inventory::GiveItem(Controller,(UFortItemDefinition*)GetResource(EFortResourceType::Metal),999,0,5,false,true,0);
 Controller->WorldInventory->HandleInventoryLocalUpdate();
 Controller->WorldInventory->ForceNetUpdate();
}