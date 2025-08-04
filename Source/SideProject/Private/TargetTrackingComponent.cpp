// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetTrackingComponent.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UTargetTrackingComponent::UTargetTrackingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UTargetTrackingComponent::BeginPlay()
{
	Super::BeginPlay();
	
	FindPlayer();
	if (IsValid(TargetActor))
	{
		GetDistanceToPlayer();
	}
}

void UTargetTrackingComponent::LateInitialize(APawn* InPawn)
{
	ControlledPawn = InPawn;
}


void UTargetTrackingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// 추적 거리 내에 있을 때만 추적
	if (IsValid(TargetActor))
	{
		
		// 마지막 위치 갱신
		LastKnownLocation = TargetActor->GetActorLocation();

		// 디버그 시각화 (시뮬레이션 중 확인용)
#if WITH_EDITOR
		DrawDebugLine(
	                    
			GetWorld(),
			ControlledPawn->GetActorLocation(),
			TargetActor->GetActorLocation(),
			FColor::Red,
			false,
			-1.0f,
			0,
			2.0f
		);
#endif
		
	}
	
}

void UTargetTrackingComponent::FindPlayer()
{
	// 기본 타겟으로 플레이어 설정
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (PlayerCharacter)
	{
		TargetActor = PlayerCharacter;
	}
}

float UTargetTrackingComponent::GetDistanceToPlayer()
{
	Distance = FVector::Dist(ControlledPawn->GetActorLocation(), TargetActor->GetActorLocation());
	return Distance;
}

void UTargetTrackingComponent::SetTarget(AActor* Target)
{
	
}
