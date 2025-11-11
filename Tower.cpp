// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
void ATower::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    //탱크와 거리 계산
    if (InFireRange()){
        RotateTurret(Tank->GetActorLocation());
    }
    
}

void ATower::HandleDestruction(){
    Super::HandleDestruction();
    Destroy();
}

void ATower::BeginPlay(){
    Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this,&ATower::ChkeckFireCondition, FireRate, true);
}
void ATower::ChkeckFireCondition(){
    if (Tank == nullptr){
        return;
    }
    if (InFireRange() && Tank->bAlive){
        Fire();
    }
}

bool ATower::InFireRange(){
    if (Tank){
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        //범위 안에 탱크 가 있는지
        if(FireRange >= Distance){
            //터렛을 탱크방향으로 돌린다
            return true;
        }
        
    }
    return false;
}