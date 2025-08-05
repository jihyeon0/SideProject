// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckState.h"

#include "AIController.h"
#include "AIStateComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_CheckState::UBTService_CheckState()
{
	NodeName = "CheckState";
	bNotifyBecomeRelevant = true;
	bNotifyTick = true;
}

void UBTService_CheckState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return;
	}

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)
	{
		return;
	}
	
	UAIStateComponent* StateComponent = ControlledPawn->FindComponentByClass<UAIStateComponent>();
	if (!StateComponent)
	{
		return;
	}

	const bool bCanAct = StateComponent->CanAct();
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("CanAct"), bCanAct);
}
