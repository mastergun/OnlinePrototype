// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine.h"
#include "MenuSystem/MenuInterface.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"
#include "PrototypeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEPROTOTYPE_API UPrototypeGameInstance : public UGameInstance ,public IMenuInterface
{
	GENERATED_BODY()
public:
	UPrototypeGameInstance(const FObjectInitializer & ObjectInitializer);
	virtual void Init();

	UFUNCTION(Exec,BlueprintCallable)
		void LoadMenu();
	UFUNCTION(Exec)
		virtual void Host() override;
	UFUNCTION(Exec)
		void Join(const FString& IPadress);
private:
	TSubclassOf<class UMainMenu> MenuReferenceClass;
	UMainMenu* menu;
};
