// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetTrackingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIDEPROJECT_API UTargetTrackingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTargetTrackingComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void LateInitialize(APawn* InPawn);
	
	UFUNCTION()
	void FindPlayer();

	UFUNCTION()
	float GetDistanceToPlayer();

	UFUNCTION()
	void SetTarget(AActor* Target);

private:
	UPROPERTY()
	TObjectPtr<AActor> TargetActor;

	UPROPERTY()
	float Distance;
	
	UPROPERTY()
	TObjectPtr<APawn> ControlledPawn;

	UPROPERTY()
	FVector LastKnownLocation;
};
