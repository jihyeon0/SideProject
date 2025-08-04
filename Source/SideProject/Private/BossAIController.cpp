// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAIController.h"

#include "TargetTrackingComponent.h"
#include "GameFramework/Character.h"              
#include "Kismet/GameplayStatics.h"        
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


ABossAIController::ABossAIController()
{

	// 시야 감지 설정 생성
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = DetectionRadius;
	SightConfig->LoseSightRadius = LoseInterestRadius;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

    TrackingComponent = CreateDefaultSubobject<UTargetTrackingComponent>(TEXT("TrackingComponent"));
}

void ABossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (TrackingComponent)
	{
		TrackingComponent->LateInitialize(InPawn);
	}
}

void ABossAIController::BeginPlay()
{
	Super::BeginPlay();

	// 인지 컴포넌트 초기화 후 컴포넌트 세팅
	if (SightConfig && GetPerceptionComponent())
	{
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
		GetPerceptionComponent()->SetDominantSense(SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ABossAIController::OnPerceptionUpdated);
	}
}

void ABossAIController::Tick(float DeltaTime)
{
	 Super::Tick(DeltaTime);
	
    // 추적 로직
    if (bIsChasing && TargetActor)
    {
        APawn* ControlledPawn = GetPawn();
        if (ControlledPawn)
        {
        }
           
    }
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
    // 플레이어 캐릭터인지 확인
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AActor* PlayerActor = Cast<AActor>(PlayerCharacter);

	if (Actor == PlayerActor)
	{
		if (Stimulus.WasSuccessfullySensed())
        {
            // 플레이어 감지 성공
            TargetActor = Actor;

            // 거리에 따라 
        }
        else
        {
            // 플레이어 감지 실패 (시야에서 사라짐)
            // 마지막으로 본 위치로 이동
            MoveToLocation(LastKnownLocation, 50.0f);

        }
    }
}