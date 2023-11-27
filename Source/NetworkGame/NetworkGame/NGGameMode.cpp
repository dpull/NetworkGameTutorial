#include "NGGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "GameFramework/ProjectileMovementComponent.h"

ANGGameMode::ANGGameMode()
{
	// PlayerControllerClass = APlayerController::StaticClass();
}

void ANGGameMode::StartPlay()
{
	Super::StartPlay();

	GameHUD = CreateWidget(GetWorld(), GameHUDClass);
	GameHUD->AddToViewport();

	SpawnNewBall();
}

void ANGGameMode::BallOverlap(AActor* OtherActor)
{
	if (OtherActor == TriggerLeft.Get())
	{
		ScoreLeft++;
	}
	else if (OtherActor == TriggerRight.Get())
	{
		ScoreRight++;
	}
	else
	{
		UE_LOG(LogNG, Log, TEXT("Ball unknown overlap:%s"), *OtherActor->GetName())
		return;
	}

	UpdateScore();
	Ball = nullptr;

	SpawnNewBall();
}

void ANGGameMode::SpawnNewBall()
{
	check(!Ball.IsValid());
	// TODO 支持等待1s

	Direction = FMath::FRandRange(-1.0f, 1.0f);
	Ball = GetWorld()->SpawnActor(BallClass.Get());
	auto ProjectileMovement = Ball->GetComponentByClass<UProjectileMovementComponent>();
	if (!ProjectileMovement)
		return;

	ProjectileMovement->Velocity = FVector(Direction * BallSpeed, 0, 0);
	ProjectileMovement->Velocity.RotateAngleAxis(FMath::FRandRange(-15.0f, 15.0f), FVector(0, 1, 0));
}

void ANGGameMode::UpdateScore()
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
