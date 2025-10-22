#include "pch.h"
#include "Gamemode.h"
#include "Utils.h"
#include "Inventory.h"
#include "Abilities.h"

void Gamemode::StartMatch()
{
 auto World=UWorld::GetWorld();
 if(!World)return;
 auto GameState=(AFortGameStateAthena*)World->GetGameState();
 auto GameMode=(AFortGameModeAthena*)World->AuthorityGameMode;
 GameMode->bMatchHasStarted=true;
 GameState->bMatchHasStarted=true;
 GameState->GamePhase=EAthenaGamePhase::Aircraft;
 GameState->OnRep_GamePhase();
 for(auto Player:GameState->PlayerArray)
 {
  auto PC=(AFortPlayerControllerAthena*)Player->GetOwner();
  if(!PC)continue;
  auto Pawn=(AFortPlayerPawnAthena*)PC->Pawn;
  if(!Pawn)
  {
   PC->ServerRestartPlayer();
   Pawn=(AFortPlayerPawnAthena*)PC->Pawn;
  }
  if(Pawn)
  {
   Pawn->SetHealth(100.f);
   Pawn->SetShield(100.f);
   Pawn->ForceNetUpdate();
   Inventory::GiveItem(PC,Utils::FindObject<UFortWeaponItemDefinition>(L"/Game/Athena/Items/Weapons/WID_Assault_AutoHigh_Athena_R_Ore_T03.WID_Assault_AutoHigh_Athena_R_Ore_T03"),1,0,1,false,true,0);
   Inventory::GiveItem(PC,Utils::FindObject<UFortWeaponItemDefinition>(L"/Game/Athena/Items/Weapons/WID_Shotgun_Standard_Athena_R_Ore_T03.WID_Shotgun_Standard_Athena_R_Ore_T03"),1,0,1,false,true,0);
   Inventory::GiveItem(PC,Utils::FindObject<UFortWeaponRangedItemDefinition>(L"/Game/Athena/Items/Weapons/WID_Sniper_BoltAction_Scope_Athena_R_Ore_T03.WID_Sniper_BoltAction_Scope_Athena_R_Ore_T03"),1,0,1,false,true,0);
   Inventory::GiveItem(PC,Utils::FindObject<UFortConsumableItemDefinition>(L"/Game/Athena/Items/Consumables/Athena_ShieldSmall.Athena_ShieldSmall"),6,0,1,false,true,0);
   Inventory::GiveItem(PC,Utils::FindObject<UFortConsumableItemDefinition>(L"/Game/Athena/Items/Consumables/Athena_Shields.Athena_Shields"),3,0,1,false,true,0);
   Inventory::GiveItem(PC,Utils::FindObject<UFortResourceItemDefinition>(L"/Game/Items/ResourcePickups/WoodItemData.WoodItemData"),999,0,1,false,true,0);
   Inventory::GiveItem(PC,Utils::FindObject<UFortResourceItemDefinition>(L"/Game/Items/ResourcePickups/StoneItemData.StoneItemData"),999,0,1,false,true,0);
   Inventory::GiveItem(PC,Utils::FindObject<UFortResourceItemDefinition>(L"/Game/Items/ResourcePickups/MetalItemData.MetalItemData"),999,0,1,false,true,0);
   Pawn->ForceNetUpdate();
  }
 }
 GameState->OnRep_MatchHasStarted();
}

void Gamemode::EndMatch()
{
 auto World=UWorld::GetWorld();
 if(!World)return;
 auto GameMode=(AFortGameModeAthena*)World->AuthorityGameMode;
 auto GameState=(AFortGameStateAthena*)World->GetGameState();
 GameMode->bMatchHasEnded=true;
 GameState->bMatchHasEnded=true;
 GameState->GamePhase=EAthenaGamePhase::EndGame;
 GameState->OnRep_GamePhase();
 for(auto Player:GameState->PlayerArray)
 {
  auto PC=(AFortPlayerControllerAthena*)Player->GetOwner();
  if(PC)
  {
   PC->ClientReturnToLobby();
  }
 }
}

void Gamemode::Hook()
{
 Utils::ExecHook(L"/Script/FortniteGame.FortGameModeAthena.StartMatch",StartMatchHook);
 Utils::ExecHook(L"/Script/FortniteGame.FortGameModeAthena.EndMatch",EndMatchHook);
}

void Gamemode::StartMatchHook(UObject* Context,FFrame&Stack)
{
 StartMatch();
}

void Gamemode::EndMatchHook(UObject* Context,FFrame&Stack)
{
 EndMatch();
}