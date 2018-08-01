// Fill out your copyright notice in the Description page of Project Settings.

#include "PrototypeGameInstance.h"
const static FName SESSION_NAME = TEXT("Host first session");

UPrototypeGameInstance::UPrototypeGameInstance(const FObjectInitializer & ObjectInitializer) {
	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_LobbyMenuClass(TEXT("/Game/Menus/WBP_LobbyMenu"));
	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_GameMenuClass(TEXT("/Game/Menus/WBP_GameMenu"));

	if (!ensure(WBP_LobbyMenuClass.Class != nullptr)) return;
	if (!ensure(WBP_GameMenuClass.Class != nullptr)) return;

	MainMenuReferenceClass = WBP_LobbyMenuClass.Class;
	GameMenuReferenceClass = WBP_GameMenuClass.Class;

	/*UE_LOG(LogTemp, Warning, TEXT("found class %s"), *WBP_LobbyMenuClass.Class->GetName());
	UE_LOG(LogTemp, Warning, TEXT("found class %s"), *WBP_GameMenuClass.Class->GetName());*/
}

void UPrototypeGameInstance::Init() {
	
	IOnlineSubsystem* subsystemReference = IOnlineSubsystem::Get();
	if (subsystemReference != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("found subsystem %s"), *subsystemReference->GetSubsystemName().ToString());
		onlineSession = subsystemReference->GetSessionInterface();
		if (onlineSession.IsValid()) {
			onlineSession->OnCreateSessionCompleteDelegates.AddUObject(this, &UPrototypeGameInstance::OnCreateSessionComplete);
			onlineSession->OnDestroySessionCompleteDelegates.AddUObject(this, &UPrototypeGameInstance::OnDestroySessionComplete);
			onlineSession->OnFindSessionsCompleteDelegates.AddUObject(this, &UPrototypeGameInstance::OnFindSessionsComplete);

			sessionSearch = MakeShareable(new FOnlineSessionSearch());
			if (sessionSearch.IsValid()) {
				UE_LOG(LogTemp, Warning, TEXT("start to find sessions"));
				//sessionSearch->bIsLanQuery = true;
				onlineSession->FindSessions(0, sessionSearch.ToSharedRef());
			}
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("found not subsystem "));
	}
	//UE_LOG(LogTemp, Warning, TEXT("found class %s"), *subsystemReference->GetName());
	/*UE_LOG(LogTemp, Warning, TEXT("found class %s"), *MainMenuReferenceClass->GetName());
	UE_LOG(LogTemp, Warning, TEXT("found class %s"), *GameMenuReferenceClass->GetName());*/
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
	if (onlineSession.IsValid()) {
		auto existingSession = onlineSession->GetNamedSession(SESSION_NAME);
		if (existingSession != nullptr) {
			onlineSession->DestroySession(SESSION_NAME);
		}
		else {
			CreateSession();
		}
	}
}

void UPrototypeGameInstance::OnDestroySessionComplete(FName sessionName, bool success) {
	if (success) {
		CreateSession();
	}
}

void UPrototypeGameInstance::OnCreateSessionComplete(FName sessionName, bool success) {
	if (!success) {
		UE_LOG(LogTemp, Warning, TEXT("the session isn't ready"));
		return;
	}
	if (mainMenu != nullptr) {
		mainMenu->TearDown();
	}
	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) return;
	world->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPrototypeGameInstance::OnFindSessionsComplete( bool success) {
	if (success && sessionSearch.IsValid()) {
		for (const FOnlineSessionSearchResult &results : sessionSearch->SearchResults) {
			UE_LOG(LogTemp, Warning, TEXT("find session completed %s"), *results.GetSessionIdStr());
		}
	}
}

void UPrototypeGameInstance::CreateSession() {
	FOnlineSessionSettings sessionSettings;
	sessionSettings.bIsLANMatch = true;
	sessionSettings.NumPublicConnections = 2;
	sessionSettings.bShouldAdvertise = true;
	onlineSession->CreateSession(0, SESSION_NAME, sessionSettings);
}

void UPrototypeGameInstance::Join(const FString& IPadress) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IP adress: ")+IPadress);

	if (mainMenu != nullptr) {
		mainMenu->TearDown();
	}

	APlayerController* playerController = GetFirstLocalPlayerController();
	if (!ensure(playerController != nullptr)) return;

	playerController->ClientTravel(IPadress, TRAVEL_Absolute);
}

void UPrototypeGameInstance::MainMenuMap() {
	if (gameMenu != nullptr) {
		gameMenu->TearDown();
	}

	APlayerController* playerController = GetFirstLocalPlayerController();
	if (!ensure(playerController != nullptr)) return;

	//per desconectar del servidor es important fer un client travel
	//per que d'aquesta manera nomes viatja l'usuari i si es el host
	//desconecta la partida. 
	playerController->ClientTravel("/Game/Maps/MainMenu", TRAVEL_Absolute);
}
