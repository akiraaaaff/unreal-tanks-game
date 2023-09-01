// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALTANKSGAME_API AUnrealTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void KillActor(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bVictory);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTurretCount(int32 RemainingTurretCount);

private:
	class ATank* Tank;
	class AUnrealTanksPlayerController* UnrealTanksPlayerController;
	float StartDelay = 3.f;
	void OnGameStart();
	int32 TurretCount;
	int32 GetTurretCount();
	
};
