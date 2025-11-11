// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawon.generated.h"


UCLASS()
class TOONTANKS_API ABasePawon : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawon();

	void HandleDestruction();
	
protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components",meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* TurretMesh;
private:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components",meta = (AllowPrivateAccess = "true"));
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components",meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components",meta = (AllowPrivateAccess = "true"));
	USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere)
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
	
};
