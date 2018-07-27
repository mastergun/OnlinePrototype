// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "MenuSystem/MenuInterface.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "GameMenu.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEPROTOTYPE_API UGameMenu : public UUserWidget
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
		void MenuOnClicked();
	UFUNCTION()
		void CancelOnClicked();
	
	UPROPERTY(meta = (BindWidget))
		UButton* MenuButton;
	UPROPERTY(meta = (BindWidget))
		UButton* CancelButton;
	IMenuInterface* menuInterface;
};
