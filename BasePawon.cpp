// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawon.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABasePawon::ABasePawon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mash"));
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawon::HandleDestruction(){
	//비주얼 사운드 이펙트 구현
	if(DeathParticle){
		UGameplayStatics::SpawnEmitterAtLocation(this,DeathParticle,GetActorLocation(),GetActorRotation());
	}
	if(DeathSound){
		UGameplayStatics::PlaySoundAtLocation(this,DeathSound,GetActorLocation());
	}
	if(DeathCameraShakeClass){
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}


// Called when the game starts or when spawned
void ABasePawon::RotateTurret(FVector LookAtTarget){
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f,ToTarget.Rotation().Yaw,0.f);
	
	TurretMesh->SetWorldRotation(FMath::RInterpTo(
		TurretMesh->GetComponentRotation(),
		 LookAtRotation,
		  UGameplayStatics::GetWorldDeltaSeconds(this),
		   5.f));
	
}

void ABasePawon::Fire(){
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
	Location,
	Rotation
	);
	Projectile->SetOwner(this);
}
// Called every frame




