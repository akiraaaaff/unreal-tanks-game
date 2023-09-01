// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	HeadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head Mesh"));
	HeadMesh->SetupAttachment(BaseMesh);

	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	ProjectileSpawn->SetupAttachment(HeadMesh);
}

void ABasePawn::OnUnitDestroy()
{
	if(DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}
	if(DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}

void ABasePawn::LookAtTarget(FVector TargetLocation)
{
	FVector DistanceToTarget = TargetLocation - HeadMesh->GetComponentLocation();
	FRotator TargetDirection = FRotator(0.f, DistanceToTarget.Rotation().Yaw, 0.f);

	HeadMesh->SetWorldRotation(
		FMath::RInterpTo(
			HeadMesh->GetComponentRotation(),
			TargetDirection,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			10.f)
		);
}

void ABasePawn::Shoot()
{
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
		ProjectileSpawn->GetComponentLocation(),
		ProjectileSpawn->GetComponentRotation()
		);

	Projectile->SetOwner(this);
	
}

