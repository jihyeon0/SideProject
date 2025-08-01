// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"

#include "BossAIController.h"

ABoss::ABoss()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

void ABoss::BeginPlay()
{
	Super::BeginPlay();

	AIController = Cast<ABossAIController>(GetController());
	if (AIController)
	{
		BlackboardComponent = AIController->GetBlackboardComponent();
	}
}

void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
