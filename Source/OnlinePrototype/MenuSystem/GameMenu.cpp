// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMenu.h"

bool UGameMenu::Initialize() {
	
	if (!Super::Initialize()) return false;

	if (!ensure(MenuButton != nullptr)) return false;
	if (!ensure(CancelButton != nullptr)) return false;

	MenuButton->OnClicked.AddDynamic(this, &UGameMenu::MenuOnClicked);
	CancelButton->OnClicked.AddDynamic(this, &UGameMenu::CancelOnClicked);
	return true;
}

void UGameMenu::MenuOnClicked() {
	if (menuInterface != nullptr) menuInterface->MainMenuMap();
}

void UGameMenu::CancelOnClicked() {
	TearDown();
}

void UGameMenu::SetMenuInterface(IMenuInterface* reference) {
	menuInterface = reference;
	if (!ensure(menuInterface != nullptr)) return;
}

void UGameMenu::Setup() {
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

void UGameMenu::TearDown() {
	this->RemoveFromViewport();

	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) return;

	APlayerController* firtsPlayerController = world->GetFirstPlayerController();
	if (!ensure(firtsPlayerController != nullptr)) return;

	firtsPlayerController->bShowMouseCursor = false;

	FInputModeGameOnly inputModeData;

	firtsPlayerController->SetInputMode(inputModeData);
}

