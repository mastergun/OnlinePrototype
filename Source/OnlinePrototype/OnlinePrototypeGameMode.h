// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PrototypeGameInstance.h" 
#include "OnlinePrototypeGameMode.generated.h"

UCLASS(minimalapi)
class AOnlinePrototypeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AOnlinePrototypeGameMode();
private:
	UFUNCTION()
		void LoadMenu();
};



