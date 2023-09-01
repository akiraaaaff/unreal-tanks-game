// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsTargetInRange())
	{
		LookAtTarget(Tank->GetActorLocation());
	}
	
}

void ATurret::OnUnitDestroy()
{
	Super::OnUnitDestroy();
	Destroy();
	
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(AttackRateTimerHandle, this, &ATurret::CheckAttackCondition, AttackRate, true);
}

void ATurret::CheckAttackCondition()
{
	if(Tank == nullptr)
	{
		return;
	}
	if(IsTargetInRange() && Tank->bAlive)
	{
		Shoot();
	}
}

bool ATurret::IsTargetInRange()
{
	if(Tank)
	{
		float DistanceToTarget = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		if(DistanceToTarget <= AttackRange)
		{
			return true;
		}
	}

	return false;
}
