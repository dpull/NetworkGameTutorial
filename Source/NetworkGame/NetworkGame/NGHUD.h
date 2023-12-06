#pragma once

#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "NGHUD.generated.h"

UCLASS(config = Game)
class ANGHUD : public AHUD
{
	GENERATED_BODY()

public:
	ANGHUD();
	virtual void BeginPlay() override;

	void UpdateScore(int32 ScoreLeft, int32 ScoreRight);

private:
	UPROPERTY(Transient)
	TSubclassOf<UUserWidget> GameHUDClass;

	UPROPERTY(Transient)
	TObjectPtr<UUserWidget> GameHUD;
};
