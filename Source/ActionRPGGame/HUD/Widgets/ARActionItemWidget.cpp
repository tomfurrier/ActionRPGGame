// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "ActionRPGGame.h"

#include "../../Types/ARStructTypes.h"
#include "../../ARPlayerController.h"
#include "../../Abilities/ARAbilityComponent.h"

#include "../../Abilities/ARAbility.h"

#include "ARCharacterSheetWidget.h"

#include "ARActionItemWidget.h"

SARActionItemWidget::~SARActionItemWidget()
{
	if (Ability.IsValid())
	{
		Ability->Destroy();
		Ability.Reset();
	}
}
void SARActionItemWidget::Construct(const FArguments& InArgs)
{
	OwnerHUD = InArgs._OwnerHUD;
	MyPC = InArgs._MyPC;
	CurrentAbility = InArgs._CurrentAbility;
	SlotType = InArgs._SlotType;
	AbilityComp = InArgs._AbilityComp;
	ActionData = nullptr;
	DrawAbility();
	ChildSlot
		[
			SNew(SBox)
			.WidthOverride(50)
			.HeightOverride(50)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				[
					SNew(SImage)
					.Image(this, &SARActionItemWidget::GetAbilityIcon)
					//SNew(STextBlock)
					//.Text(FText::FromName("Buton"))
				]
				+ SOverlay::Slot()
				[
					SNew(STextBlock)
					.ShadowColorAndOpacity(FLinearColor::Black)
					.ColorAndOpacity(FLinearColor::White)
					.ShadowOffset(FIntPoint(-1, 1))
					.Font(FSlateFontInfo("Veranda", 16))
					.Text(this, &SARActionItemWidget::GetCurrentCooldown)
				]

			]
		];
}

void SARActionItemWidget::DrawAbility()
{
	if (AbilityComp.IsValid())
	{
		if (AbilityComp->AbiltityDataTemp.Num() > 0 && CurrentAbility->ActionIndex >= 0
			&& AbilityComp->AbiltityDataTemp.IsValidIndex(CurrentAbility->ActionIndex))
			ActionData = &AbilityComp->AbiltityDataTemp[CurrentAbility->ActionIndex];
	}
}

FText SARActionItemWidget::GetCurrentCooldown() const
{
	if (AbilityComp.IsValid())
	{
		if (CurrentAbility->Ability.IsValid())
		{
			if (CurrentAbility->Ability->IsOnCooldown)
			{
				return FText::AsNumber(CurrentAbility->Ability->CurrentCooldownTime);
			}
		}

	}
	return FText::AsNumber(0);
}

const FSlateBrush* SARActionItemWidget::GetAbilityIcon() const
{
	//FSlateBrush* icon = NULL;
	//AbilityIcon = NULL;
	if (ActionData)
	{
		return &ActionData->AbilityIcon;
	}

	return nullptr;
}

//Mouse Input
void SARActionItemWidget::OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{
	//TSharedPtr<FDragDropOperation> Operation = DragDropEvent.GetOperation();

	//TSharedPtr<FDragDropOperation> Operation = DragDropEvent.GetOperationAs<FAbilityDragDrop>();
}
void SARActionItemWidget::OnDragLeave(const FDragDropEvent& DragDropEvent)
{
	//TSharedPtr<FInventoryDragDrop> Operation2 = DragDropEvent.GetOperationAs<FInventoryDragDrop>();

	//Operation2->LastItemSlot->InventoryItem = Operation2->PickedItem;
}
FReply SARActionItemWidget::OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{
	TSharedPtr<FAbilityDragDrop> Operation = DragDropEvent.GetOperationAs<FAbilityDragDrop>();
	if (Operation.IsValid())
	{
		Operation->SetDecoratorVisibility(true);
	}

	return FReply::Handled();
}
FReply SARActionItemWidget::OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{
	TSharedPtr<FAbilityDragDrop> Operation = DragDropEvent.GetOperationAs<FAbilityDragDrop>();

	if (!Operation.IsValid())
		return FReply::Unhandled();

	/*
		If last slot type was Inventory we just equip ability, to the current slot.
		If the last slot type was HotBar it means we want to swap abilities with positions.
	*/
	if (Operation->LastAbilitySlot->SlotType == EARAbilitySlot::Ability_Inventory)
	{
		if (!AbilityComp.IsValid())
			return FReply::Unhandled();

		AbilityComp->AddAbilityToActionBar(*Operation->PickedAbility, this->CurrentAbility->SlotIndex, 0);
		return FReply::Handled();
	}
	else if (Operation->LastAbilitySlot->SlotType == EARAbilitySlot::Ability_ActionBar)
	{

	}

	return FReply::Unhandled();
}
void SARActionItemWidget::OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	//TextColor = FSlateColor(FLinearColor(0, 1, 0, 1));
}
void SARActionItemWidget::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	//TextColor = FSlateColor(FLinearColor(1, 0, 0, 1));
}
FReply SARActionItemWidget::OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	TSharedRef<FAbilityDragDrop> Operation = FAbilityDragDrop::New(CurrentAbility, SharedThis(this));
	Operation->SetDecoratorVisibility(true);
	return FReply::Handled().BeginDragDrop(Operation);
}

FReply SARActionItemWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (CurrentAbility.IsValid())
	{
		return FReply::Handled().DetectDrag(SharedThis(this), MouseEvent.GetEffectingButton()).CaptureMouse(SharedThis(this));
	}
	return FReply::Unhandled();
}
FReply SARActionItemWidget::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	return FReply::Handled().ReleaseMouseCapture();
}




TSharedRef<FAbilityDragDrop> FAbilityDragDrop::New(TSharedPtr<FActionSlotInfo> PickedItemIn, TSharedPtr<SARActionItemWidget> LastAbilitySlotIn)
{
	TSharedRef<FAbilityDragDrop> Operation = MakeShareable(new FAbilityDragDrop);
	Operation->ActionData = nullptr;
	Operation->PickedAbility = PickedItemIn;
	Operation->LastAbilitySlot = LastAbilitySlotIn;
	Operation->Construct();
	return Operation;
}

TSharedPtr<SWidget> FAbilityDragDrop::GetDefaultDecorator() const
{
	return SNew(SBorder).Cursor(EMouseCursor::GrabHandClosed)
		.Content()
		[
			SNew(STextBlock)
			.ShadowColorAndOpacity(FLinearColor::Black)
			.ColorAndOpacity(FLinearColor::White)
			.ShadowOffset(FIntPoint(-1, 1))
			.Font(FSlateFontInfo("Veranda", 16)) //don't believe this works, see Rama's tutorial
			//.Text(FText::FromName(PickedItem->ItemName))
			.Text(FText::FromName("Picked.Item"))
			//SNew(SImage)
			//.Image(this, &FInventoryDragDrop::GetDecoratorIcon)
		];
}

const FSlateBrush* FAbilityDragDrop::GetDecoratorIcon() const
{
	FSlateBrush* image = NULL;

	//if (InventoryItemObj.IsValid())
	//{
	//	image = &InventoryItemObj->ItemIcon;
	//}

	return image;
}