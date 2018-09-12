// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Engine.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEPROTOTYPE_API UServerRow : public UUserWidget
{
	GENERATED_BODY()
public:
	//UServerRow(const FObjectInitializer &ObjectInitializer);
	UPROPERTY(meta = (BindWidget))
		UTextBlock* ServerText;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* NumOfPlayers;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* HostName;
	UPROPERTY(blueprintReadOnly)
		bool isCliked;
	void Setup(class UScrollBarMenu* menu, uint32 index);	
	void UpdateRow();
protected:
	//virtual bool Initialize() override;
private:
	UFUNCTION()
		void RowButtonOnClicked();
	UPROPERTY(meta = (BindWidget))
		UButton* RowButton;
	UPROPERTY()
		class UScrollBarMenu* menuRef;
	UPROPERTY()
		uint32 rowIndex;
};
