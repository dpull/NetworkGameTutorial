// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "NGHud.h"

#include "UObject/ConstructorHelpers.h"

ANGHud::ANGHud()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDClass(TEXT("/Game/Blueprints/WG_GameHUD"));
	if (HUDClass.Succeeded())
	{
		GameHUDClass = HUDClass.Class;
	}
}

void ANGHud::BeginPlay()
{
	Super::BeginPlay();
	GameHUD = CreateWidget(GetWorld(), GameHUDClass);
	GameHUD->AddToViewport();
}

void ANGHud::UpdateScore(int32 ScoreLeft, int32 ScoreRight)
{
	FName ScoreText[] = { FName(TEXT("Update Cpu Score Text")), FName(TEXT("Update Player Score Text")) };
	int32 Score[] = { ScoreLeft, ScoreRight };
	
	for (int i = 0; i < _countof(ScoreText); ++i)
	{
		auto Function = GameHUD->FindFunction(ScoreText[i]);
		if (!Function)
			return;
		GameHUD->ProcessEvent(Function, Score + i);
	}
}
