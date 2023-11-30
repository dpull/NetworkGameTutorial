#pragma once

#include "GameFramework/GameStateBase.h"
#include "NGGameState.generated.h"

UCLASS()
class ANGGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > &OutLifetimeProps) const override;

	void AddScore(int32 InAddLeft, int32 InAddRight);
	
private:
	UFUNCTION()
	virtual void OnRep_Score();
	
	UPROPERTY(Transient, ReplicatedUsing = OnRep_Score)
	int32 ScoreLeft;
	UPROPERTY(Transient, ReplicatedUsing = OnRep_Score)
	int32 ScoreRight;
};
