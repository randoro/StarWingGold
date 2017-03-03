// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "StarWing.h"
#include "StarWingGameMode.h"
#include "StarWingPawn.h"
#include "Blueprint/UserWidget.h" //"Runtime/UMG/Public/Blueprint/UserWidget.h"

AStarWingGameMode::AStarWingGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = AStarWingPawn::StaticClass();
}

void AStarWingGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (HUDWidgetClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
		
	}
}

void AStarWingGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time--;
	if (Health < 1.0f) {
		Health += 0.0001f;
	}
	if (Boost < 1.0f) {
		Boost += 0.005f;
	}
	if (Time < 0) {
		//Gameover
		Reason = "You ran out of time!";
		UGameplayStatics::OpenLevel(GetWorld(), "GameOverTime");
	}
	if (Health < 0.0f) {
		//Gameover
		Reason = "You ran out of health!";
		UGameplayStatics::OpenLevel(GetWorld(), "GameOverHealth");
	}
}

int32 AStarWingGameMode::GetTime() 
{
	return Time;
}

float AStarWingGameMode::GetHealth()
{
	return Health;
}

float AStarWingGameMode::GetBoost()
{
	return Boost;
}

FString AStarWingGameMode::GetReason()
{
	return Reason;
}

void AStarWingGameMode::SetTime(int32 NewTime) 
{
	Time = NewTime;
}

void AStarWingGameMode::SetHealth(float NewHealth)
{
	Health = NewHealth;
}

void AStarWingGameMode::SetBoost(float NewBoost)
{
	Boost = NewBoost;
}