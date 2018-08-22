// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerRow.h"
#include "MenuSystem/ScrollBarMenu.h"


void UServerRow::Setup(class UScrollBarMenu* menu, uint32 index) {
	menuRef = menu;
	rowIndex = index;
	isCliked = false;
	RowButton->OnClicked.AddDynamic(this, &UServerRow::RowButtonOnClicked);
}

void UServerRow::UpdateRow() {
	/*
	if (isCliked) {	
		this->SetColorAndOpacity(FLinearColor(0.0f,1.0f,0.0f,1.0f));
	}
	else {
		this->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	}*/
}

void UServerRow::RowButtonOnClicked() {
	if (menuRef != nullptr) {
		menuRef->SelectIndex(rowIndex);
	}
}




