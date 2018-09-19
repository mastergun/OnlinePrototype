// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"

//ALobbyGameMode::ALobbyGameMode() {
//	playersCounter = 0;
//}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer) {
	Super::PostLogin(NewPlayer);
	playersCounter++;
	UE_LOG(LogTemp, Warning, TEXT("players in lobby %d"), playersCounter);
	if (playersCounter >= 3) {
		UWorld* world = GetWorld();
		if (!ensure(world != nullptr)) return;
		
		bUseSeamlessTravel = true;
		world->ServerTravel("/Game/Maps/Game?listen");
	}
}

void ALobbyGameMode::Logout(AController* Exiting) {
	Super::Logout(Exiting);
	playersCounter--;
	UE_LOG(LogTemp, Warning, TEXT("players in lobby %d"), playersCounter);

}
