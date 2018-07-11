// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() {
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
	finalPos = FVector(0.0f, 0.0f, 0.0f);
	SetState(State::Autonomous);
	triggersToActivate = 0;
}

void AMovingPlatform::BeginPlay() {
	Super::BeginPlay();
	if (HasAuthority()) {
		initPos = GetActorLocation();
		finalPos = GetTransform().TransformPosition(finalPos); // amb aquesta funcio, transformes una pos local a global. si utilitzes el metode inverseTransformPosition, es per convertir de global a local
		SetDirection();
		SetState(type);
		SetReplicates(true); // informa que l'objecte s'ha de replicar en els clients 
		SetReplicateMovement(true); //informa que el moviment del objecte s'ha de replicar en els clients
		moving = false;
	}
}

void AMovingPlatform::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (HasAuthority()) {
		if (moving) {
			FVector Location = GetActorLocation();
			Location += dir*DeltaTime;
			SetActorLocation(Location);

			if (PasedPoint()) {
				FVector newFinalPos = initPos;
				initPos = finalPos;
				finalPos = newFinalPos;
				SetDirection();
				timer = waitingTime;
				if(type == State::Autonomous) moving = false;
			}
		}
		else {
			if (type == State::Autonomous) {
				timer -= DeltaTime;
				if (timer <= 0) moving = true;
			}
		}
	}
}

void AMovingPlatform::SetDirection() {
	dir = finalPos - initPos;
	dir.Normalize();
	dir *= velocity;
}

bool AMovingPlatform::PasedPoint() {
	FVector toFinalPoint = finalPos - GetActorLocation();
	float distance = FVector::DotProduct(dir, toFinalPoint);
	if (distance <= 0)return true;
	else return false;
}

void AMovingPlatform::SetState(State state) {
	type = state;
	if (type == State::Autonomous)timer = waitingTime;
	else if (type == State::Controlled)timer = 0;
}

void AMovingPlatform::SetIsMoving(bool isMoving) {
	//save the order of a trigger
	if (isMoving)numOfTriggers++;
	else numOfTriggers--;

	//set the movement of the platform
	if (numOfTriggers >= triggersToActivate) moving = true;
	else moving = false;
}

