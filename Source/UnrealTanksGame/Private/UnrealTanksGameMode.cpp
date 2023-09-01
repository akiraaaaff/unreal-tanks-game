// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealTanksGameMode.h"

#include "Tank.h"
#include "Turret.h"
#include "UnrealTanksPlayerController.h"
#include "Kismet/GameplayStatics.h"

void AUnrealTanksGameMode::KillActor(AActor* DeadActor)
{
	if(DeadActor == Tank)
	{
		Tank->OnUnitDestroy();
		if(UnrealTanksPlayerController)
		{
			UnrealTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATurret* DestroyedTurret = Cast<ATurret>(DeadActor))
	{
		DestroyedTurret->OnUnitDestroy();
		TurretCount--;
		UpdateTurretCount(TurretCount);
		if(TurretCount <= 0)
		{
			GameOver(true);
		}
	}
	
}

void AUnrealTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	OnGameStart();
}

void AUnrealTanksGameMode::OnGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	UnrealTanksPlayerController = Cast<AUnrealTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	TurretCount = GetTurretCount();

	StartGame();
	
	if(UnrealTanksPlayerController)
	{
		UnrealTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(UnrealTanksPlayerController, &AUnrealTanksPlayerController::SetPlayerEnabledState, true);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
	}
}

int32 AUnrealTanksGameMode::GetTurretCount()
{
	TArray<AActor*> Turrets;
	UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), Turrets);
	return Turrets.Num();
}
