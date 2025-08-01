// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BossAIController.generated.h"


class UAISenseConfig_Sight;
class UBehaviorTreeComponent;


// AI 상태 열거형 정의
UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,
	Suspicious, //의심하는 상태 추가
	Chasing
};

UCLASS()
class SIDEPROJECT_API ABossAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABossAIController();
	
	// 추적할 타겟(플레이어, 추후 에디터에서 설정)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	AActor* TargetActor;
	
	// 추적 시작/중지 함수
	UFUNCTION(BlueprintCallable, Category = "AI")
	void StartChasing(AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void StopChasing();

	// 추적 거리 설정 1000유닌(10m)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float ChaseRadius = 1000.0f;

	// 시야 감지 설정
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAISenseConfig_Sight* SightConfig;

	// 감지 이벤트 처리 함수
	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	// 상태 변환 함수
	UFUNCTION(BlueprintCallable, Category = "AI")
	void UpdateAIState();
	
	// 거리 설정 변수 추가
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float DetectionRadius = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float LoseInterestRadius = 2000.0f;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	// 타겟 추적 중인지 여부
	bool bIsChasing = false;
	// 현재 상태 변수
	EAIState CurrentState = EAIState::Idle;
	// 마지막으로 타겟을 본 위치 저장
	FVector LastKnownLocation;
};