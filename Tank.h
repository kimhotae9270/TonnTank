// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawon.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawon
{
	GENERATED_BODY()
public:
	ATank();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

	bool bAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components",meta = (AllowPrivateAccess = "true"));
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components",meta = (AllowPrivateAccess = "true"));
	class UCameraComponent* Camera;
	void Move(float Value);
	UPROPERTY(EditAnywhere)
	float Speed = 200.f;
	UPROPERTY(EditAnywhere)
	float TurnRate = 45.f;
	void Turn(float Value);
	
	APlayerController* TankPlayerController;

	
};
