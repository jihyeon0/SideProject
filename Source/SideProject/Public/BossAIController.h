// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionTypes.h"
#include "BossAIController.generated.h"


struct FAIStimulus;
class UTargetTrackingComponent;

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
	
	UPROPERTY(BlueprintReadWrite, Category = "AI", SaveGame)  // 실행중인 컴포넌트
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(BlueprintReadWrite, Category = "AI", SaveGame)
	UBlackboardComponent* BlackboardComponent;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Perception")
	UAIPerceptionComponent* PerceptionComp;
	
	// 시야 감지 설정
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Perception")
	UAISenseConfig_Sight* SightConfig;

	// 감지 이벤트 처리 함수
	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
	// 거리 설정 변수 추가
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float DetectionRadius = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float LoseInterestRadius = 2000.0f;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UTargetTrackingComponent> TrackingComponent;
	
private:
	bool bIsChasing = false;
	
	// 마지막으로 타겟을 본 위치
	FVector LastKnownLocation;
};