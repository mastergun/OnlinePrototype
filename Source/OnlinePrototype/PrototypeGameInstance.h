// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine.h"
#include "MenuSystem/MenuInterface.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionInterface.h"
#include "MenuSystem/ScrollBarMenu.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/GameMenu.h"
#include "MenuSystem/BaseMenu.h"
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
	//virtual UPrototypeGameInstance* GetSelfReference() override;
	UFUNCTION(Exec, BlueprintCallable)
		virtual void LoadScrollBarMenu() override;
	UFUNCTION(Exec, BlueprintCallable)
		void LoadMainMenu();
	UFUNCTION(Exec)
		virtual void Host() override;
	UFUNCTION(Exec)
		void Join(const uint32 id);
	UFUNCTION(Exec)
		void JoinIP(const FString IPAdress);
	UFUNCTION(Exec)
		void HostWithSessionName(const FName HostName);
	UFUNCTION(Exec)
		void FindSessions();
	UFUNCTION(Exec, BlueprintCallable)
		virtual void LoadGameMenu() override;
	UFUNCTION(Exec)
		virtual void MainMenuMap() override;
private:
	TSubclassOf<class UMainMenu> MainMenuReferenceClass;
	TSubclassOf<class UScrollBarMenu> ScrollBarMenuReferenceClass;
	TSubclassOf<class UGameMenu> GameMenuReferenceClass;

	UScrollBarMenu* scrollBarMenu;
	UMainMenu* mainMenu;
	UGameMenu* gameMenu;
	FString session_Name;

	void OnCreateSessionComplete(FName sessionName, bool success);
	void OnDestroySessionComplete(FName sessionName, bool success);
	void OnFindSessionsComplete(bool success);
	void OnJoinSessionComplete(FName sessionName, EOnJoinSessionCompleteResult::Type result);

	//TArray<FServerData> serverNames;
	TSharedPtr<FOnlineSessionSearch> sessionSearch;
	IOnlineSessionPtr onlineSession;

	void CreateSession();
};
