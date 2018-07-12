// Fill out your copyright notice in the Description page of Project Settings.

#include "PrototypeGameInstance.h"

UPrototypeGameInstance::UPrototypeGameInstance(const FObjectInitializer & ObjectInitializer) {
	UE_LOG(LogTemp, Warning, TEXT("prototype game instance constructor called"));
}

void UPrototypeGameInstance::Init() {
	UE_LOG(LogTemp, Warning, TEXT("prototype game instance Init function called"));
}

void UPrototypeGameInstance::Host() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Host function called"));

	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) return;
	world->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPrototypeGameInstance::Join(const FString& IPadress) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IP adress: ")+IPadress);

	APlayerController* playerController = GetFirstLocalPlayerController();
	if (!ensure(playerController != nullptr)) return;

	playerController->ClientTravel(IPadress, TRAVEL_Relative);
}
