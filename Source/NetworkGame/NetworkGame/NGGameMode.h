#pragma once

#include "GameFramework/GameMode.h"
#include "NGGameMode.generated.h"

UCLASS()
class ANGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANGGameMode();
	virtual void StartPlay() override;

	void BallOverlap(AActor* OtherActor);
	AActor* GetBall() { return Ball.Get(); }

private:
	void SpawnNewBall();
	void UpdateScore();

private:
	UPROPERTY(EditAnywhere, NoClear, Category = Classes)
	TSubclassOf<AActor> BallClass;
	UPROPERTY(EditAnywhere, NoClear, Category = Classes)
	TSubclassOf<UUserWidget> GameHUDClass;

	UPROPERTY()
	TWeakObjectPtr<AActor> Ball;
	UPROPERTY()
	TObjectPtr<UUserWidget> GameHUD;

	UPROPERTY(EditAnywhere, Category = Trigger)
	TSoftObjectPtr<AActor> TriggerLeft;
	UPROPERTY(EditAnywhere, Category = Trigger)
	TSoftObjectPtr<AActor> TriggerRight;

	int32 ScoreLeft = 0;
	int32 ScoreRight = 0;

	float BallSpeed = 1600;
	float Direction = 0;
};
