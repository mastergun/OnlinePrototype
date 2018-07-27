// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMenu.h"

void UBaseMenu::SetMenuInterface(IMenuInterface* reference) {
	menuInterface = reference;
	if (!ensure(menuInterface != nullptr)) return;
}

void UBaseMenu::Setup() {
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

void UBaseMenu::TearDown() {
	this->RemoveFromViewport();

	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) return;

	APlayerController* firtsPlayerController = world->GetFirstPlayerController();
	if (!ensure(firtsPlayerController != nullptr)) return;

	firtsPlayerController->bShowMouseCursor = false;

	FInputModeGameOnly inputModeData;

	firtsPlayerController->SetInputMode(inputModeData);
}


