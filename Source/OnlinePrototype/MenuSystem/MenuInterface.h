// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ONLINEPROTOTYPE_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Host()= 0;
	virtual void Join(const uint32 id) = 0;
	virtual void JoinIP(const FString IPAdress) = 0;
	virtual void FindSessions() = 0;
	virtual void MainMenuMap() = 0;
	virtual void LoadGameMenu() = 0;
	virtual void LoadScrollBarMenu() = 0;
	//virtual void GetSelfReference() = 0;
};
