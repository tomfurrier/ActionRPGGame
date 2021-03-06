// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "ARAttributeBaseComponent.h"
#include "../Types/ARStructTypes.h"

#include "ARAttributeComponent.generated.h"

/*
	Add this component to player controller or character ?
*/

UCLASS(hidecategories = (Object, LOD, Lighting, Transform, Sockets, TextureStreaming), editinlinenew, meta = (BlueprintSpawnableComponent))
class UARAttributeComponent : public UARAttributeBaseComponent
{
	GENERATED_UCLASS_BODY()
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	virtual void OnRegister() override;

	virtual void InitializeComponent() override;

	/*
		Called after properties are set and replicated. From actor which owns component.
	*/
	virtual void Initialize() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_Health, Category = "Derived Attribute")
		float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Health, Category = "Derived Attribute")
		float Energy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Health, Category = "Derived Attribute")
		float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Health, Category = "Derived Attribute")
		float Strenght;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Health, Category = "Derived Attribute")
		float Dexterity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Health, Category = "Derived Attribute")
		float Constitution;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Health, Category = "Derived Attribute")
		float Magic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Health, Category = "Derived Attribute")
		float Intelligence;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Derived Attribute")
		float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Derived Attribute")
		float MaxEnergy;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Derived Attribute")
		float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Derived Attribute")
		float Armor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Derived Attribute")
		float AttackPower;

	UFUNCTION()
		void OnRep_Health();

	TArray<class UAREffectType*> DefaultEffects;

	UPROPERTY(EditAnywhere, Category = "Default Feats")
	TArray<TSubclassOf<class UAREffectType> > DefaultEffectClasses;

	UFUNCTION(BlueprintCallable, Category = "AR|Debug")
		void DebugAddFeat(TSubclassOf<class UAREffectType> FeatIn);

};



