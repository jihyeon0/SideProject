// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAIController.h"

#include "Boss.h"
#include "TargetTrackingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"              
#include "Kismet/GameplayStatics.h"       


ABossAIController::ABossAIController()
{
	// 시야 감지 설정 생성
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1000.f;
	SightConfig->LoseSightRadius = 1500.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
	
    TrackingComponent = CreateDefaultSubobject<UTargetTrackingComponent>(TEXT("TrackingComponent"));
}

void ABossAIController::BeginPlay()
{
	Super::BeginPlay();
	
	PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ABossAIController::OnPerceptionUpdated);
	
}

void ABossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (BehaviorTree)
	{
		// 이전까지 멤버변수 BlackboardComponent = nullptr일 가능성 높음
		UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent); 
		// 블랙보드 초기화 성공, 비헤이비어 트리 실행
		RunBehaviorTree(BehaviorTree);
	}
	
	if (TrackingComponent)
	{
		TrackingComponent->LateInitialize(InPawn);
	}
}

void ABossAIController::Tick(float DeltaTime)
{
	 Super::Tick(DeltaTime);
	
}

void ABossAIController::StartChasing(AActor* Target)
{
   
    bIsChasing = true;
        
}

void ABossAIController::StopChasing()
{
    bIsChasing = false;

}

void ABossAIController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AActor* PlayerActor = Cast<AActor>(PlayerCharacter);

	if (Actor == PlayerActor)
	{
		if (Stimulus.WasSuccessfullySensed())
        {
            TargetActor = Actor;
			BlackboardComponent->SetValueAsObject("TargetActor",TargetActor);
			
        }
        else
        {
            // 플레이어 감지 실패 (시야에서 사라짐)
            // 마지막으로 본 위치로 이동
            MoveToLocation(LastKnownLocation, 50.0f);
        }
    }
}