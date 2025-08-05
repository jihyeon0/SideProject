// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "AIStateComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStateChanged, FGameplayTag, Tag, bool, bAdded);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIDEPROJECT_API UAIStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAIStateComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void AddStateTag(FGameplayTag Tag);
	void RemoveStateTag(FGameplayTag Tag);
	bool HasStateTag(FGameplayTag Tag) const;
	bool CanAct() const;
	
	UPROPERTY(BlueprintAssignable)
	FOnStateChanged OnStateChanged;
	
protected:
	virtual void BeginPlay() override;

private:
	void NotifyStateChange(FGameplayTag Tag, bool bAdded);
	bool IsDead() const;

	FGameplayTagContainer ActiveTags;
};
