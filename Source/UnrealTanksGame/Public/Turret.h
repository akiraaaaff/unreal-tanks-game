// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class UNREALTANKSGAME_API ATurret : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	void OnUnitDestroy();

protected:
	virtual void BeginPlay() override;

private:
	class ATank* Tank;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float AttackRange = 250.f;

	FTimerHandle AttackRateTimerHandle;
	float AttackRate = 2.f;
	void CheckAttackCondition();
	bool IsTargetInRange();
	
};
