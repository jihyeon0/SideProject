// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CheckState.generated.h"

/**
 * 
 */
UCLASS()
class SIDEPROJECT_API UBTService_CheckState : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_CheckState();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};