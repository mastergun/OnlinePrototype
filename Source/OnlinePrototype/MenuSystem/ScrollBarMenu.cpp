// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrollBarMenu.h"

UScrollBarMenu::UScrollBarMenu(const FObjectInitializer & ObjectInitializer) {
	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_ServerRowClass(TEXT("/Game/Menus/WBP_ServerRow"));
	if (!ensure(WBP_ServerRowClass.Class != nullptr)) return;
	ServerRowReferenceClass = WBP_ServerRowClass.Class;
}

bool UScrollBarMenu::Initialize() {
	if (!Super::Initialize()) return false;

	if (!ensure(HostButton != nullptr)) return false;
	if (!ensure(JoinButton != nullptr)) return false;
	if (!ensure(JoinMenuButton != nullptr)) return false;
	if (!ensure(CancelButton != nullptr)) return false;
	if (!ensure(QuitButton != nullptr)) return false;

	HostButton->OnClicked.AddDynamic(this, &UScrollBarMenu::HostOnClicked);
	JoinButton->OnClicked.AddDynamic(this, &UScrollBarMenu::JoinOnClicked);
	JoinMenuButton->OnClicked.AddDynamic(this, &UScrollBarMenu::LoadJoinMenu);
	CancelButton->OnClicked.AddDynamic(this, &UScrollBarMenu::LoadMainMenu);
	QuitButton->OnClicked.AddDynamic(this, &UScrollBarMenu::QuitGame);

	return true;
}

void UScrollBarMenu::SetServerList(TArray<FServerData> ServerNames) {
	if (!ensure(ServerScroll != nullptr)) return;
	ServerScroll->ClearChildren();

	UWorld* world = this->GetWorld();
	if (!ensure(world != nullptr)) return;
	uint32 index = 0;
	for (const FServerData& serverData : ServerNames) {
		UServerRow* serverRow = CreateWidget<UServerRow>(world, ServerRowReferenceClass);
		if (!ensure(serverRow != nullptr)) return;
		serverRow->Setup(this, index);
		serverRow->ServerText->SetText(FText::FromString(serverData.serverName));
		serverRow->HostName->SetText(FText::FromString(serverData.hostUserName));
		serverRow->NumOfPlayers->SetText(FText::FromString(FString::FromInt(serverData.numOfPlayers) + "/" + FString::FromInt(serverData.maxPlayers)));
		ServerScroll->AddChild(serverRow);
		index++;
	}
}

void UScrollBarMenu::HostOnClicked() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Client atempting to Join"));
	if (menuInterface != nullptr) menuInterface->Host();
}

void UScrollBarMenu::SelectIndex(uint32 index){
	rowIndex = index;
	UpdateRows(index);
}

void UScrollBarMenu::UpdateRows(int index){
	for (int32 i = 0;i < ServerScroll->GetChildrenCount();i++){
		UServerRow* row = Cast<UServerRow>(ServerScroll->GetChildAt(i));
		if(row != nullptr){
			row->isCliked = (rowIndex.IsSet() && rowIndex.GetValue() == i);
		}	
	}
}

void UScrollBarMenu::JoinOnClicked() {
	//if (!ensure(ServerScroll != nullptr)) return;
	
	if (menuInterface != nullptr) {
		if (rowIndex.IsSet()) {
			menuInterface->Join(rowIndex.GetValue());
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("session doesn't found"));
		}
	}
	
}

void UScrollBarMenu::LoadJoinMenu() {
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
	menuInterface->FindSessions();
}

void UScrollBarMenu::LoadMainMenu() {
	ServerScroll->ClearChildren();
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UScrollBarMenu::QuitGame() {
	APlayerController* playerController = GetOwningPlayer();
	if (!ensure(playerController != nullptr)) return;

	playerController->ConsoleCommand("Quit");
}



