#pragma once

#include "GameFramework/GameMode.h"
#include "NGGameMode.generated.h"

class ANGBall;

UCLASS()
class ANGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANGGameMode();
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void StartPlay() override;
	virtual void RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot) override;

	void OnBallOverlap(ANGBall* Ball, AActor* OtherActor);
	void OnBallHit(ANGBall* Ball, AActor* OtherActor);

	void RegisterPawnForAutoReceiveInput(APawn* InPawn);

private:
	UPROPERTY(EditAnywhere, Category = Trigger)
	TSoftObjectPtr<AActor> TriggerLeft;
	UPROPERTY(EditAnywhere, Category = Trigger)
	TSoftObjectPtr<AActor> TriggerRight;

	TArray<TWeakObjectPtr<APawn>> PendingAutoReceiveInputPawns;
};
