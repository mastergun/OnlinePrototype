// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

bool UMainMenu::Initialize() {
	if (!Super::Initialize()) return false;

	if (!ensure(HostButton != nullptr)) return false;
	if (!ensure(JoinButton != nullptr)) return false;
	if (!ensure(JoinMenuButton != nullptr)) return false;
	if (!ensure(CancelButton != nullptr)) return false;
	
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostOnClicked);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinOnClicked);
	JoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::LoadJoinMenu);
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::LoadMainMenu);
	return true;
	
}

void UMainMenu::HostOnClicked() {
	if (menuInterface != nullptr) menuInterface->Host();
}

void UMainMenu::JoinOnClicked() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Client atempting to Join"));
	if (!ensure(IPAdressInput != nullptr)) return;
	if (menuInterface != nullptr) menuInterface->Join(IPAdressInput->GetText().ToString());
	UE_LOG(LogTemp, Warning, TEXT("joinning"));
}

void UMainMenu::LoadJoinMenu() {
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::LoadMainMenu() {
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::SetMenuInterface(IMenuInterface* reference) {
	menuInterface = reference;
	if (!ensure(menuInterface != nullptr)) return;
}

void UMainMenu::Setup() {
	this->AddToViewport();
	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) return;

	APlayerController* firtsPlayerController = world->GetFirstPlayerController();
	if (!ensure(firtsPlayerController != nullptr)) return;

	FInputModeUIOnly inputModeData;
	inputModeData.SetWidgetToFocus(this->TakeWidget());
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	firtsPlayerController->SetInputMode(inputModeData);
	firtsPlayerController->bShowMouseCursor = true;
}

void UMainMenu::TearDown() {
	this->RemoveFromViewport();

	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) return;

	APlayerController* firtsPlayerController = world->GetFirstPlayerController();
	if (!ensure(firtsPlayerController != nullptr)) return;

	firtsPlayerController->bShowMouseCursor = false;

	FInputModeGameOnly inputModeData;
	//inputModeData.SetConsumeCaptureMouseDown(false);

	firtsPlayerController->SetInputMode(inputModeData);
}