#pragma once
#include "framework.h"

namespace Abilities
{
 void Hook();
 void ServerStartJump(UObject* Context,FFrame&Stack);
 void ServerStopJump(UObject* Context,FFrame&Stack);
 void ServerBeginCrouch(UObject* Context,FFrame&Stack);
 void ServerEndCrouch(UObject* Context,FFrame&Stack);
 void UseJetpack(AFortPlayerPawn* Pawn);
 void UseImpulseGrenade(AFortPlayerPawn* Pawn);
 void DeployGlider(AFortPlayerPawn* Pawn);
 void PlaceTrap(AFortPlayerController* Controller);
 void ResetFallVelocity(AFortPlayerPawn* Pawn);
}