// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/Math/Vector.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class State : uint8
{
	Autonomous 	UMETA(DisplayName = "Autonomous"),
	Controlled 	UMETA(DisplayName = "Controlled")
};

UCLASS()
class ONLINEPROTOTYPE_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	AMovingPlatform();
	void BeginPlay();
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		float velocity;
	UPROPERTY(EditAnywhere)
		float waitingTime;
	UPROPERTY(EditAnywhere, Meta=(MakeEditWidget = true))
		FVector finalPos; // aquest vector estara en pos local del objecte en questio. 
	void SetDirection();
	bool PasedPoint();
	void SetState(State state);
	void SetIsMoving(bool isMoving);

private:
	FVector initPos;
	FVector dir;
	bool moving;
	float timer;
	UPROPERTY(EditAnywhere)
		State type;
	
};
