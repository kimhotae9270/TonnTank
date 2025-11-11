// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawon.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawon
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	class ATank* Tank;
	UPROPERTY(EditDefaultsOnly)
	float FireRange = 300.f;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	void ChkeckFireCondition();

	bool InFireRange();
};
