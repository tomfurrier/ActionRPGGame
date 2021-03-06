// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "ActionRPGGame.h"

#include "../Types/AREnumTypes.h"

#include "../BlueprintLibrary/ARTraceStatics.h"
#include "../ARCharacter.h"
#include "../Items/ARWeapon.h"

#include "ParticleHelper.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

#include "Net/UnrealNetwork.h"

#include "ARTrailCue.h"

UARTrailCue::UARTrailCue(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	SetIsReplicated(true);

	bWantsInitializeComponent = true;
	bAutoRegister = true;
}
void UARTrailCue::InitializeComponent()
{
	Super::InitializeComponent();

	OriginWeapon = Cast<AARWeapon>(GetOwner());
}
void UARTrailCue::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UARTrailCue, HitInfo);
}

void UARTrailCue::OnRep_Hit()
{
	SimulateHitOnClients(HitInfo.Origin, HitInfo.Location, HitInfo.StartSocket);
}
void UARTrailCue::SimulateHitOnClients(FVector Origin, FVector Location, FName StartSocketIn)
{
	if (TrailFX)
	{
		//AARWeapon* weap = Cast<AARWeapon>(GetOwner());
		if (OriginWeapon)
		{
			FVector locOrigin = UARTraceStatics::GetStartLocation(StartSocket, OriginWeapon->WeaponOwner, OriginWeapon->WeaponHand);
			TrailPSC = UGameplayStatics::SpawnEmitterAtLocation(GetOwner(), TrailFX, locOrigin);
			if (TrailPSC)
			{
				const FVector AdjustedDir = (Location - locOrigin).SafeNormal();
				FVector ParticleSpeed = AdjustedDir * TrailSpeed2;
				TrailPSC->SetVectorParameter(TrailSpeedParam2, ParticleSpeed);
			}
		}
	}
}

void UARTrailCue::SpawnEffectOnOwner()
{
	if (GetNetMode() == ENetMode::NM_Standalone)
		OnRep_Hit();
}
void UARTrailCue::OnCollide(FName EventName, float EmitterTime, int32 ParticleTime, FVector Location, FVector Velocity, FVector Direction, FVector Normal, FName BoneName)
{
	if (TrailPSC)
	{
		TrailPSC->Deactivate();
		TrailPSC->DestroyComponent();
	}
}
//void UARTrailCue::SetOnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//
//}