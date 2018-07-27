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

