// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "MenuSystem/MenuInterface.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEPROTOTYPE_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetMenuInterface(IMenuInterface* reference);
	void Setup();
	void TearDown();
protected:
	virtual bool Initialize() override;
private:
	UFUNCTION()
	void HostOnClicked();
	UFUNCTION()
	void JoinOnClicked();
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
	UWidgetSwitcher* MenuSwitcher;
	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;
	UPROPERTY(meta = (BindWidget))
	UWidget* MainMenu;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* IPAdressInput;

	
	IMenuInterface* menuInterface;
};