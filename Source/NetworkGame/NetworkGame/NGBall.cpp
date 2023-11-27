#include "NGBall.h"
#include "NGGameMode.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ANGBall::BeginPlay()
{
	Super::BeginPlay();
}

void ANGBall::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	auto GameMode = GetWorld()->GetAuthGameMode<ANGGameMode>();
	if (GameMode)
	{
		GameMode->BallOverlap(OtherActor);
	}
}
