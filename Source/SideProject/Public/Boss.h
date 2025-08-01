// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Boss.generated.h"

class UBlackboardComponent;
class ABossAIController;

UCLASS()
class SIDEPROJECT_API ABoss : public ACharacter
{
	GENERATED_BODY()

public:
	ABoss();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	ABossAIController* AIController;
	
	UPROPERTY()
	UBlackboardComponent* BlackboardComponent;
};
