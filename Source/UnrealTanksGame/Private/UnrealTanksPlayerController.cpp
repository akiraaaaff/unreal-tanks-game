// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealTanksPlayerController.h"

void AUnrealTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	if(bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
}
