// Fill out your copyright notice in the Description page of Project Settings.

#include "PrototypeGameInstance.h"
const static FName SESSION_NAME = TEXT("Game");
const static FName SESSION_NAME_SETINGS_KEY = TEXT("SessionName");

UPrototypeGameInstance::UPrototypeGameInstance(const FObjectInitializer & ObjectInitializer) {
	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_LobbyMenuClass(TEXT("/Game/Menus/WBP_LobbyMenu"));
	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_ScrollBarClass(TEXT("/Game/Menus/WBP_ScrollBarMenu"));
	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_GameMenuClass(TEXT("/Game/Menus/WBP_GameMenu"));

	if (!ensure(WBP_LobbyMenuClass.Class != nullptr)) return;
	if (!ensure(WBP_ScrollBarClass.Class != nullptr)) return;
	if (!ensure(WBP_GameMenuClass.Class != nullptr)) return;

	MainMenuReferenceClass = WBP_LobbyMenuClass.Class;
	GameMenuReferenceClass = WBP_GameMenuClass.Class;
	ScrollBarMenuReferenceClass = WBP_ScrollBarClass.Class;
	
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
			onlineSession->OnJoinSessionCompleteDelegates.AddUObject(this, &UPrototypeGameInstance::OnJoinSessionComplete);
			//sessionSearch = MakeShareable(new FOnlineSessionSearch());
			//if (sessionSearch.IsValid()) {
			//	UE_LOG(LogTemp, Warning, TEXT("start to find sessions"));
			//	sessionSearch->bIsLanQuery = true;
			//	onlineSession->FindSessions(0, sessionSearch.ToSharedRef());
			//}
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("found not subsystem "));
	}
	//UE_LOG(LogTemp, Warning, TEXT("found class %s"), *subsystemReference->GetName());
	/*UE_LOG(LogTemp, Warning, TEXT("found class %s"), *MainMenuReferenceClass->GetName());
	UE_LOG(LogTemp, Warning, TEXT("found class %s"), *GameMenuReferenceClass->GetName());*/
}
void UPrototypeGameInstance::LoadScrollBarMenu() {
	if (!ensure(ScrollBarMenuReferenceClass != nullptr)) return;
	scrollBarMenu = CreateWidget<UScrollBarMenu>(this, ScrollBarMenuReferenceClass);
	if (!ensure(scrollBarMenu != nullptr)) return;

	scrollBarMenu->Setup();
	scrollBarMenu->SetMenuInterface(this);
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
	UE_LOG(LogTemp, Warning, TEXT("hosting without name session"));
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

void UPrototypeGameInstance::HostWithSessionName(const FName HostName) {
	UE_LOG(LogTemp, Warning, TEXT("hosting with name session"));
	session_Name = HostName.ToString();
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
	if (scrollBarMenu != nullptr) {
		scrollBarMenu->TearDown();
	}
	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) return;
	//world->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
	world->ServerTravel("/Game/Maps/Lobby?listen");
	
}

void UPrototypeGameInstance::OnFindSessionsComplete( bool success) {
	if (success && sessionSearch.IsValid() && scrollBarMenu != nullptr) {
		TArray<FServerData> serverNames;
		for (const FOnlineSessionSearchResult &results : sessionSearch->SearchResults) {
			UE_LOG(LogTemp, Warning, TEXT("find session completed %s"), *results.GetSessionIdStr());
			FServerData data;
			//data.serverName = results.GetSessionIdStr();
			FString dataName;
			if (results.Session.SessionSettings.Get(SESSION_NAME_SETINGS_KEY, dataName)) {
				data.serverName = dataName;
			}
			else {
				data.serverName = results.GetSessionIdStr();
			}

			data.hostUserName = results.Session.OwningUserName;
			data.numOfPlayers = results.Session.NumOpenPublicConnections;
			data.maxPlayers = results.Session.SessionSettings.NumPublicConnections;
			
			serverNames.Add(data);
		}

		scrollBarMenu->SetServerList(serverNames);
		UE_LOG(LogTemp, Warning, TEXT("find session finished"));
	}
}

void UPrototypeGameInstance::OnJoinSessionComplete(FName sessionName, EOnJoinSessionCompleteResult::Type result) {
	if (!onlineSession.IsValid())return;
	FString adress;
	if (!onlineSession->GetResolvedConnectString(sessionName, adress)) {
		UE_LOG(LogTemp, Warning, TEXT("error to joinning session"));
		return;
	}

	APlayerController* playerController = GetFirstLocalPlayerController();
	if (!ensure(playerController != nullptr)) return;
	playerController->ClientTravel(adress, TRAVEL_Absolute);
}

void UPrototypeGameInstance::CreateSession() {
	FOnlineSessionSettings sessionSettings;
	//si aquesta opcio esta a true, nomes es podran fer sesions en LAN
	if(IOnlineSubsystem::Get()->GetSubsystemName().ToString() == "NULL" ){
		sessionSettings.bIsLANMatch = true; 
	}
	else {
		sessionSettings.bIsLANMatch = false;
	}
	sessionSettings.NumPublicConnections = 2;
	sessionSettings.bShouldAdvertise = true;
	//si posem la presence a true, ens permetrar crear lobbies.
	//si esta a false es per crear sessions en internet propies.
	//per aquesta ultima opccio segurament sera necesari comprar el servidor dedicat d'steam
	sessionSettings.bUsesPresence = true;
	sessionSettings.Set(SESSION_NAME_SETINGS_KEY, session_Name,EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	onlineSession->CreateSession(0, SESSION_NAME, sessionSettings);
}

void UPrototypeGameInstance::FindSessions(){
	sessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (sessionSearch.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("start to find sessions"));
		//sessionSearch->bIsLanQuery = false;
		sessionSearch->MaxSearchResults = 1000;
		sessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		onlineSession->FindSessions(0, sessionSearch.ToSharedRef());
	}		
}

void UPrototypeGameInstance::Join(const uint32 id) {
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IP adress: ")+IPadress);
	if (!onlineSession.IsValid())return;
	if (!sessionSearch.IsValid())return;

	if (scrollBarMenu != nullptr) {
		scrollBarMenu->TearDown();
	}

	onlineSession->JoinSession(0, SESSION_NAME, sessionSearch->SearchResults[id]);
}

void UPrototypeGameInstance::JoinIP(const FString IPAdress) {
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IP adress: ")+IPadress);

	if (mainMenu != nullptr) {
		mainMenu->TearDown();
	}

	APlayerController* playerController = GetFirstLocalPlayerController();
	if (!ensure(playerController != nullptr)) return;

	playerController->ClientTravel(IPAdress, TRAVEL_Absolute);
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



