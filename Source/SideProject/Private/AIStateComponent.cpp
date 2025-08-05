#include "AIStateComponent.h"

UAIStateComponent::UAIStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UAIStateComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UAIStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UAIStateComponent::HasStateTag(FGameplayTag Tag) const
{
	return ActiveTags.HasTagExact(Tag);
}

void UAIStateComponent::AddStateTag(FGameplayTag Tag)
{
	if (!ActiveTags.HasTagExact(Tag))
	{
		ActiveTags.AddTag(Tag);
		NotifyStateChange(Tag, true);
	}
}

void UAIStateComponent::RemoveStateTag(FGameplayTag Tag)
{
	if (ActiveTags.HasTagExact(Tag))
	{
		ActiveTags.RemoveTag(Tag);
		NotifyStateChange(Tag, false);
	}
}

void UAIStateComponent::NotifyStateChange(FGameplayTag Tag, bool bAdded)
{
	OnStateChanged.Broadcast(Tag, bAdded);
}


bool UAIStateComponent::IsDead() const
{
	return HasStateTag(FGameplayTag::RequestGameplayTag("AI.State.Dead")); //태그 고여챠앟ㅁ
}

bool UAIStateComponent::CanAct() const
{
	return !IsDead() && !HasStateTag(FGameplayTag::RequestGameplayTag("AI.State.Busy"));
}