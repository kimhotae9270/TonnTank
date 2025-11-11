// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
ATank::ATank(){
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    SpringArm->SetupAttachment(RootComponent);
    Camera->SetupAttachment(SpringArm);

}

void ATank::HandleDestruction(){
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
}


void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"),this, &ATank::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);

}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankPlayerController = Cast<APlayerController>(GetController());

    
}
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TankPlayerController){
        FHitResult Hitresult;
        TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,
        false,
        Hitresult
        );
        RotateTurret(Hitresult.ImpactPoint);
        }

       

}

void ATank::Move(float Value){
    FVector DeltaLocation(0.f);
    DeltaLocation.X = Value*Speed*UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(DeltaLocation, true);
    //UE_LOG(LogTemp, Display, TEXT("%f"),DeltaLocation.X);
}

void ATank::Turn(float Value){
    FRotator DeltaRotator = FRotator::ZeroRotator;
    DeltaRotator.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotator,true);
}
