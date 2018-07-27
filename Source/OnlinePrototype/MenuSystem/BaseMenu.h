// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MenuInterface.h"
#include "BaseMenu.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEPROTOTYPE_API UBaseMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetMenuInterface(IMenuInterface* reference);
	void Setup();
	void TearDown();
protected:
	IMenuInterface* menuInterface;
};
