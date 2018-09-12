// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "MenuSystem/BaseMenu.h"
#include "MenuSystem/ServerRow.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/PanelWidget.h"
#include "MenuSystem/ServerRow.h"
#include "ScrollBarMenu.generated.h"


USTRUCT()
struct FServerData {
	GENERATED_BODY()

	FString serverName;
	FString hostUserName;
	int16 numOfPlayers;
	int16 maxPlayers;
};
/**
 * 
 */
UCLASS()
class ONLINEPROTOTYPE_API UScrollBarMenu : public UBaseMenu
{
	GENERATED_BODY()
public:
	UScrollBarMenu(const FObjectInitializer & ObjectInitializer);
	void SetServerList(TArray<FServerData> ServerNames);
	void SelectIndex(uint32 index);
protected:
	virtual bool Initialize() override;
private:
	UFUNCTION()
		void HostOnClicked();
	UFUNCTION()
		void JoinOnClicked();
	UFUNCTION()
		void QuitGame();
	UFUNCTION()
		void LoadJoinMenu();
	UFUNCTION()
		void LoadMainMenu();

	UPROPERTY(meta = (BindWidget))
		UButton* HostButton;
	UPROPERTY(meta = (BindWidget))
		UButton* JoinButton;
	UPROPERTY(meta = (BindWidget))
		UButton* JoinMenuButton;
	UPROPERTY(meta = (BindWidget))
		UButton* CancelButton;
	UPROPERTY(meta = (BindWidget))
		UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* MenuSwitcher;
	UPROPERTY(meta = (BindWidget))
		UWidget* JoinMenu;
	UPROPERTY(meta = (BindWidget))
		UWidget* MainMenu;
	UPROPERTY(meta = (BindWidget))
		UPanelWidget* ServerScroll;

	TSubclassOf<UServerRow> ServerRowReferenceClass;
	TOptional<uint32> rowIndex;
	void UpdateRows(int index);
};
