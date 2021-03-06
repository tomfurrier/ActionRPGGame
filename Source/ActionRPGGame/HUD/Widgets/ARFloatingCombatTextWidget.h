// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "../ARHUD.h"

#include "../../Types/ARStructTypes.h"

#include "Slate.h"

class SARFloatingCombatTextWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SARFloatingCombatTextWidget)
	{}
	/*See private declaration of OwnerHUD below.*/
		SLATE_ARGUMENT(TWeakObjectPtr<class AARHUD>, OwnerHUD)

		SLATE_ARGUMENT(TWeakObjectPtr<class AARPlayerController>, MyPC)

		SLATE_ARGUMENT(TWeakObjectPtr<class UARAttributeComponent>, MyAttrComp)

		SLATE_ARGUMENT(TWeakObjectPtr<class AActor>, TargetActor)

		SLATE_ARGUMENT(float, DisplayNumber)
	SLATE_END_ARGS()

public:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Needed for every widget
	/////Builds this widget and any of it's children
	void Construct(const FArguments& InArgs);
	void CreateDamageText();
	float CurrentLifeTime;
	virtual void SARFloatingCombatTextWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	//virtual int32 OnPaint(const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
private:

	//TSharedPtr<SCanvas> WidgetCanvas;

	TWeakObjectPtr<class AARHUD> OwnerHUD;

	TWeakObjectPtr<class AARPlayerController> MyPC;

	TWeakObjectPtr<class AARCharacter> MyChar;

	TWeakObjectPtr<class UARAttributeComponent> MyAttrComp;

	TWeakObjectPtr<class AActor> TargetActor;

	float DisplayNumber;
	FVector2D Projecte(FVector VectorIn) const;
	TAttribute<FVector2D> CurrentPosition;
	FVector2D GetCurrentPosition() const;
	TSharedPtr<SOverlay> TextBlock;
};



