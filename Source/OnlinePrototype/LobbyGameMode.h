// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlinePrototypeGameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEPROTOTYPE_API ALobbyGameMode : public AOnlinePrototypeGameMode
{
	GENERATED_BODY()

public:
	//ALobbyGameMode();
	void PostLogin(APlayerController* NewPlayer) override;
	void Logout(AController* Exiting) override;

private:
	uint32 playersCounter = 0;
};
