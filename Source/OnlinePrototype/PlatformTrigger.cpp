// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformTrigger.h"


// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	triggerZone = CreateDefaultSubobject<UBoxComponent>(FName("triggerZone"));
	if (!ensure(triggerZone != nullptr)) return;
	RootComponent = triggerZone;

	triggerZone->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapBegin);
	triggerZone->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformTrigger::OnOverlapBegin(	class UPrimitiveComponent* OverlappedComp, 
										class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
										int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	UE_LOG(LogTemp, Warning , TEXT("the platform still activated"));
	if (conectedPlatforms.Num() != 0) {
		for (AMovingPlatform* movingPlatform : conectedPlatforms) {
			//movingPlatform->SetIsMoving(true);
			movingPlatform->SetIsMoving(true);
		}
	}
}
void APlatformTrigger::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
									class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	UE_LOG(LogTemp, Warning, TEXT("the platform still deactivated"));
	if (conectedPlatforms.Num() != 0) {
		for (AMovingPlatform* movingPlatform : conectedPlatforms) {
			//movingPlatform->SetIsMoving(true);
			movingPlatform->SetIsMoving(false);
		}
	}
}

