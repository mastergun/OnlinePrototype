// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() {
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
	finalPos = FVector(0.0f, 0.0f, 0.0f);
}

void AMovingPlatform::BeginPlay() {
	Super::BeginPlay();
	initPos = GetActorLocation();
	SetVelocity();
}

void AMovingPlatform::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (HasAuthority()) {
		FVector Location = GetActorLocation();
		Location += velocity*DeltaTime;
		SetActorLocation(Location);

		if (finalPos.Distance(finalPos, GetActorLocation()) <= 10.0f) {
			FVector newFinalPos = initPos;
			initPos = finalPos;
			finalPos = newFinalPos;
			SetVelocity();
		}
	}
}

void AMovingPlatform::SetVelocity() {
	velocity = finalPos - initPos;
	velocity = velocity.GetSafeNormal();
	velocity *= acceleration;
}

