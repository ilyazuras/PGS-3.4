#include "pch.h"
#include "Inventory.h"
#include "Utils.h"

UFortItemDefinition* Inventory::GiveItem(AFortPlayerControllerAthena* Controller,UFortItemDefinition* ItemDef,int Count,int LoadedAmmo,int Slot,bool Equip,bool Update,int EntryIndex)
{
 if(!Controller||!ItemDef)return nullptr;
 auto World=UWorld::GetWorld();
 auto Pawn=(AFortPlayerPawnAthena*)Controller->Pawn;
 if(!Pawn)return nullptr;
 auto Inventory=Controller->WorldInventory;
 if(!Inventory)return nullptr;
 FFortItemEntry Entry{};
 Entry.Count=Count;
 Entry.ItemDefinition=ItemDef;
 Entry.LoadedAmmo=LoadedAmmo;
 Entry.Durability=1.f;
 EntryEntryGuid=FGuid::NewGuid();
 Inventory->Inventory.ReplicatedEntries.Add(Entry);
 if(Update)Inventory->HandleInventoryLocalUpdate();
 if(Equip)Pawn->EquipWeapon(ItemDef);
 Inventory->ForceNetUpdate();
 return ItemDef;
}

void Inventory::ClearInventory(AFortPlayerControllerAthena* Controller)
{
 if(!Controller)return;
 auto Inventory=Controller->WorldInventory;
 if(!Inventory)return;
 Inventory->Inventory.ReplicatedEntries.Clear();
 Inventory->HandleInventoryLocalUpdate();
 Inventory->ForceNetUpdate();
}

void Inventory::RemoveItem(AFortPlayerControllerAthena* Controller,UFortItemDefinition* ItemDef)
{
 if(!Controller||!ItemDef)return;
 auto Inventory=Controller->WorldInventory;
 if(!Inventory)return;
 for(int i=0;i<Inventory->Inventory.ReplicatedEntries.Num();i++)
 {
  if(Inventory->Inventory.ReplicatedEntries[i].ItemDefinition==ItemDef)
  {
   Inventory->Inventory.ReplicatedEntries.RemoveAt(i);
   break;
  }
 }
 Inventory->HandleInventoryLocalUpdate();
 Inventory->ForceNetUpdate();
}

void Inventory::HandleInventoryLocalUpdate(AFortPlayerControllerAthena* Controller)
{
 if(!Controller)return;
 auto Inventory=Controller->WorldInventory;
 if(!Inventory)return;
 static void(*HandleLocalUpdate)(UFortInventory*)=decltype(HandleLocalUpdate)(ImageBase+0x5D47B30);
 HandleLocalUpdate(Inventory);
 Inventory->ForceNetUpdate();
}