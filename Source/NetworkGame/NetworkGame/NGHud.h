// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "NGHud.generated.h"

UCLASS(config = Game)
class ANGHud : public AHUD
{
	GENERATED_BODY()

public:
	ANGHud();
	virtual void BeginPlay() override;
	
	void UpdateScore(int32 ScoreLeft, int32 ScoreRight);

private:
	UPROPERTY(Transient)
	TSubclassOf<UUserWidget> GameHUDClass;
	
	UPROPERTY(Transient)
	TObjectPtr<UUserWidget> GameHUD;
};
