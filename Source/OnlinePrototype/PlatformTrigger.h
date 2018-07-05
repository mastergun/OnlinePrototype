// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MovingPlatform.h"
#include "PlatformTrigger.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FComponentEndOverlapSignature, class AActor*, OtherActor, class UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex);

UCLASS(BlueprintType)
class ONLINEPROTOTYPE_API APlatformTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* triggerZone;
	UPROPERTY(EditAnywhere)
		TArray<class AMovingPlatform*> conectedPlatforms;
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
							class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, 
							const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(	class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
							class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
