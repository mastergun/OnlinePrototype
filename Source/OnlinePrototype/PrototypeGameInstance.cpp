// Fill out your copyright notice in the Description page of Project Settings.

#include "PrototypeGameInstance.h"


UPrototypeGameInstance::UPrototypeGameInstance(const FObjectInitializer & ObjectInitializer) {
	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_LobbyMenuClass(TEXT("/Game/Menus/WBP_LobbyMenu"));
	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_GameMenuClass(TEXT("/Game/Menus/WBP_GameMenu"));

	if (!ensure(WBP_LobbyMenuClass.Class != nullptr)) return;
	if (!ensure(WBP_GameMenuClass.Class != nullptr)) return;

	MainMenuReferenceClass = WBP_LobbyMenuClass.Class;
	GameMenuReferenceClass = WBP_GameMenuClass.Class;

	UE_LOG(LogTemp, Warning, TEXT("found class %s"), *WBP_LobbyMenuClass.Class->GetName());
	UE_LOG(LogTemp, Warning, TEXT("found class %s"), *WBP_GameMenuClass.Class->GetName());
}

void UPrototypeGameInstance::Init() {
	UE_LOG(LogTemp, Warning, TEXT("found class %s"), *MainMenuReferenceClass->GetName());
	UE_LOG(LogTemp, Warning, TEXT("found class %s"), *GameMenuReferenceClass->GetName());
}

void UPrototypeGameInstance::LoadMainMenu() {
	if (!ensure(MainMenuReferenceClass != nullptr)) return;
	mainMenu = CreateWidget<UMainMenu>(this, MainMenuReferenceClass);
	if (!ensure(mainMenu != nullptr)) return;

	mainMenu->Setup();
	mainMenu->SetMenuInterface(this);

}

void UPrototypeGameInstance::LoadGameMenu() {

	if (!ensure(GameMenuReferenceClass != nullptr)) return;
	gameMenu = CreateWidget<UGameMenu>(this, GameMenuReferenceClass);
	if (!ensure(gameMenu != nullptr)) return;

	gameMenu->Setup();
	gameMenu->SetMenuInterface(this);
}

void UPrototypeGameInstance::Host() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Host function called"));
	if (mainMenu != nullptr) {
		mainMenu->TearDown();
	}

	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) return;

	world->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPrototypeGameInstance::Join(const FString& IPadress) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IP adress: ")+IPadress);

	if (mainMenu != nullptr) {
		mainMenu->TearDown();
	}

	APlayerController* playerController = GetFirstLocalPlayerController();
	if (!ensure(playerController != nullptr)) return;

	playerController->ClientTravel(IPadress, TRAVEL_Relative);
}

void UPrototypeGameInstance::MainMenuMap() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("travel to main menu map called"));
	if (gameMenu != nullptr) {
		gameMenu->TearDown();
	}

	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) return;

	world->ServerTravel("/Game/Maps/MainMenu?listen");
}