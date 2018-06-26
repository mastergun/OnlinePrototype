// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/Math/Vector.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEPROTOTYPE_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	AMovingPlatform();
	void BeginPlay();
	virtual void Tick(float DeltaTime) override;
	FVector velocity;
	UPROPERTY(EditAnywhere)
		float acceleration;
	FVector initPos;
	UPROPERTY(EditAnywhere)
		FVector finalPos;
	void SetVelocity();
};
