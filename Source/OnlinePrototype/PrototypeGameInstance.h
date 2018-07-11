// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine.h"
#include "PrototypeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEPROTOTYPE_API UPrototypeGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPrototypeGameInstance(const FObjectInitializer & ObjectInitializer);
	virtual void Init();
	UFUNCTION(Exec)
		void Host();
	UFUNCTION(Exec)
		void Join(const FString& IPadress);
};
