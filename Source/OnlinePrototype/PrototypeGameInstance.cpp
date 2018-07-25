// Fill out your copyright notice in the Description page of Project Settings.

#include "PrototypeGameInstance.h"


UPrototypeGameInstance::UPrototypeGameInstance(const FObjectInitializer & ObjectInitializer) {
	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_LobbyMenuClass(TEXT("/Game/Menus/WBP_LobbyMenu"));
	if (!ensure(WBP_LobbyMenuClass.Class != nullptr)) return;
	MenuReferenceClass = WBP_LobbyMenuClass.Class;
	
	UE_LOG(LogTemp, Warning, TEXT("found class %s"), *WBP_LobbyMenuClass.Class->GetName());
}

void UPrototypeGameInstance::Init() {
	UE_LOG(LogTemp, Warning, TEXT("found class %s"), *MenuReferenceClass->GetName());
}

void UPrototypeGameInstance::LoadMenu() {
	if (!ensure(MenuReferenceClass != nullptr)) return;
	menu = CreateWidget<UMainMenu>(this, MenuReferenceClass);
	if (!ensure(menu != nullptr)) return;

	menu->Setup();
	menu->SetMenuInterface(this);

}

void UPrototypeGameInstance::Host() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Host function called"));
	if (menu != nullptr) {
		menu->TearDown();
	}

	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) return;

	world->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPrototypeGameInstance::Join(const FString& IPadress) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IP adress: ")+IPadress);

	if (menu != nullptr) {
		menu->TearDown();
	}

	APlayerController* playerController = GetFirstLocalPlayerController();
	if (!ensure(playerController != nullptr)) return;

	playerController->ClientTravel(IPadress, TRAVEL_Relative);
}
