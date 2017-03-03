// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "StarWingGameMode.generated.h"

UCLASS(minimalapi)
class AStarWingGameMode : public AGameMode
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;

	UPROPERTY(VisibleAnywhere)
	int32 Time = 2000;

	UPROPERTY(VisibleAnywhere)
	float Health = 1.0f;

	UPROPERTY(VisibleAnywhere)
	float Boost = 1.0f;

public:
	AStarWingGameMode();

	void BeginPlay();

	void Tick(float DeltaTime);

	UFUNCTION(BlueprintPure, Category = "Time")
	int32 GetTime();

	UFUNCTION(BlueprintPure, Category = "Time")
	float GetHealth();

	UFUNCTION(BlueprintPure, Category = "Time")
	float GetBoost();

	UFUNCTION(Category = "Time")
	void SetTime(int32 NewTime);

	UFUNCTION(Category = "Time")
	void SetHealth(float NewHealth);

	UFUNCTION(Category = "Time")
	void SetBoost(float NewBoost);
};



