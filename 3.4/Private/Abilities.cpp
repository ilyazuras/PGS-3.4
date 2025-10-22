#include "pch.h"
#include "Abilities.h"
#include "Utils.h"
#include "Inventory.h"

void Abilities::ServerStartJump(UObject* Context,FFrame&Stack)
{
 auto Pawn=(AFortPlayerPawn*)Context;
 if(!Pawn)return;
 Pawn->CharacterMovement->DoJump(false);
 Pawn->ForceNetUpdate();
}

void Abilities::ServerStopJump(UObject* Context,FFrame&Stack)
{
 auto Pawn=(AFortPlayerPawn*)Context;
 if(!Pawn)return;
 Pawn->CharacterMovement->StopJumping();
 Pawn->ForceNetUpdate();
}

void Abilities::ServerBeginCrouch(UObject* Context,FFrame&Stack)
{
 auto Pawn=(AFortPlayerPawn*)Context;
 if(!Pawn)return;
 Pawn->bIsCrouched=true;
 Pawn->CharacterMovement->Crouch(false);
 Pawn->ForceNetUpdate();
}

void Abilities::ServerEndCrouch(UObject* Context,FFrame&Stack)
{
 auto Pawn=(AFortPlayerPawn*)Context;
 if(!Pawn)return;
 Pawn->bIsCrouched=false;
 Pawn->CharacterMovement->UnCrouch(false);
 Pawn->ForceNetUpdate();
}

void Abilities::UseJetpack(AFortPlayerPawn* Pawn)
{
 if(!Pawn)return;
 auto Jetpack=Inventory::GiveItem(Pawn->Controller->Cast<AFortPlayerController>(),
 Utils::FindObject<UFortWeaponItemDefinition>(L"/Game/Athena/Items/Weapons/WID_Jetpack_Athena_SR.WID_Jetpack_Athena_SR"),
 1,0,1,false,true,0);
 if(Jetpack)
 {
  Pawn->EquipWeapon(Jetpack->ItemEntry.ItemDefinition);
  Pawn->PlayAnimMontage(Utils::FindObject<UAnimMontage>(L"/Game/Animations/Jetpack_Activate_Montage.Jetpack_Activate_Montage"));
  Pawn->ForceNetUpdate();
 }
}

void Abilities::UseImpulseGrenade(AFortPlayerPawn* Pawn)
{
 if(!Pawn)return;
 FVector LaunchVelocity=Pawn->GetActorForwardVector()*1500.f+FVector(0,0,800);
 Pawn->LaunchCharacter(LaunchVelocity,false,true);
 Pawn->PlayAnimMontage(Utils::FindObject<UAnimMontage>(L"/Game/Animations/Impulse_Throw_Montage.Impulse_Throw_Montage"));
 Pawn->ForceNetUpdate();
}

void Abilities::DeployGlider(AFortPlayerPawn* Pawn)
{
 if(!Pawn)return;
 if(Pawn->CharacterMovement->IsFalling())
 {
  Pawn->CharacterMovement->Velocity.Z=0;
  Pawn->PlayAnimMontage(Utils::FindObject<UAnimMontage>(L"/Game/Animations/Glider_Open_Montage.Glider_Open_Montage"));
  Pawn->ForceNetUpdate();
 }
}

void Abilities::PlaceTrap(AFortPlayerController* Controller)
{
 if(!Controller)return;
 auto Trap=Inventory::GiveItem(Controller,
 Utils::FindObject<UFortTrapItemDefinition>(L"/Game/Athena/Items/Traps/WID_FloorSpikes_Athena_R.WID_FloorSpikes_Athena_R"),
 1,0,1,false,true,0);
 if(Trap)
 {
  Controller->ServerPlaceBuilding(Trap->ItemEntry.ItemDefinition);
 }
}

void Abilities::ResetFallVelocity(AFortPlayerPawn* Pawn)
{
 if(!Pawn)return;
 Pawn->CharacterMovement->Velocity.Z=0;
 Pawn->ForceNetUpdate();
}

void Abilities::Hook()
{
 Utils::ExecHook(L"/Script/FortniteGame.FortPlayerPawn.ServerJump",ServerStartJump);
 Utils::ExecHook(L"/Script/FortniteGame.FortPlayerPawn.ServerStopJumping",ServerStopJump);
 Utils::ExecHook(L"/Script/FortniteGame.FortPlayerPawn.ServerBeginCrouch",ServerBeginCrouch);
 Utils::ExecHook(L"/Script/FortniteGame.FortPlayerPawn.ServerEndCrouch",ServerEndCrouch);
}