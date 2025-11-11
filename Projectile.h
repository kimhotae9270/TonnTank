// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnyWhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit
	);
	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(EditAnywhere)
	UParticleSystem* HitParticles;

	UPROPERTY(VisibleAnyWhere)
	class UParticleSystemComponent* ParticleComponent;

	UPROPERTY(EditAnywhere)
	class USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
