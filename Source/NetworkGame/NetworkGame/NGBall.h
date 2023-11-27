#pragma once

#include "GameFramework/Character.h"
#include "NGBall.generated.h"

UCLASS(config = Game)
class ANGBall : public APawn
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor);
};
