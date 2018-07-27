// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Components/Button.h"
#include "BaseMenu.h"
#include "GameMenu.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEPROTOTYPE_API UGameMenu : public UBaseMenu
{
	GENERATED_BODY()
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
};
