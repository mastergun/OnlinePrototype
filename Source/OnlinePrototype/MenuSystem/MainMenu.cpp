// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

bool UMainMenu::Initialize() {
	if (!Super::Initialize()) return false;

	if (!ensure(HostButton != nullptr)) return false;
	if (!ensure(JoinButton != nullptr)) return false;
	if (!ensure(JoinMenuButton != nullptr)) return false;
	if (!ensure(CancelButton != nullptr)) return false;
	if (!ensure(QuitButton != nullptr)) return false;
	
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostOnClicked);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinOnClicked);
	JoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::LoadJoinMenu);
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::LoadMainMenu);
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	return true;
}

void UMainMenu::HostOnClicked() {
	if (menuInterface != nullptr) menuInterface->Host();
}

void UMainMenu::JoinOnClicked() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Client atempting to Join"));
	if (!ensure(IPAdressInput != nullptr)) return;
	if (menuInterface != nullptr) menuInterface->JoinIP(IPAdressInput->GetText().ToString());
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

void UMainMenu::QuitGame() {
	APlayerController* playerController = GetOwningPlayer();
	if (!ensure(playerController != nullptr)) return;

	playerController->ConsoleCommand("Quit");
}