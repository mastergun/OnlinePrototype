// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "OnlinePrototypeGameMode.h"
#include "OnlinePrototypeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOnlinePrototypeGameMode::AOnlinePrototypeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
	/*UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) return;

	APlayerController* firtsPlayerController = world->GetFirstPlayerController();
	if (!ensure(firtsPlayerController != nullptr)) return;
	firtsPlayerController->InputComponent->BindAction("OpenGameMenu", IE_Pressed, this, &AOnlinePrototypeGameMode::LoadMenu);*/
}

void AOnlinePrototypeGameMode::LoadMenu() {
}
