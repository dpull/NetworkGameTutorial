#include "NGGameMode.h"

#include "NGBall.h"
#include "NGGameState.h"
#include "NGHud.h"
#include "NGPawn.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Level.h"
#include "Engine/World.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/ProjectileMovementComponent.h"

ANGGameMode::ANGGameMode()
{
	GameStateClass = ANGGameState::StaticClass();
	HUDClass = ANGHud::StaticClass();
}

void ANGGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	GameSession->MaxPlayers = 2;
}

void ANGGameMode::StartPlay()
{
	Super::StartPlay();
}

void ANGGameMode::RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot)
{
	auto CurPawn = NewPlayer->GetPawn();
	if (CurPawn)
	{
		bool bFind = false;
		for (auto Pawn : PendingAutoReceiveInputPawns)
		{
			if (Pawn == CurPawn)
			{
				bFind = true;
				break;
			}
		}
		if (!bFind)
		{
			NewPlayer->Possess(nullptr);
			CurPawn = nullptr;
		}
	}

	if (!CurPawn)
	{
		for (auto Pawn : PendingAutoReceiveInputPawns)
		{
			if (!Cast<APlayerController>(Pawn->GetController()))
			{
				CurPawn = Pawn.Get();
				break;
			}
		}
	}

	if (!CurPawn)
	{
		FailedToRestartPlayer(NewPlayer);
		return;
	}
	
	NewPlayer->Possess(CurPawn);
	Super::RestartPlayerAtPlayerStart(NewPlayer, StartSpot);
}

void ANGGameMode::OnBallOverlap(ANGBall* InBall, AActor* InOtherActor)
{
	FTimerHandle DummyHandle;
	GetWorld()->GetTimerManager().SetTimer(DummyHandle, [InBall]()
	{
		InBall->Destroy();
	}, 0.3f, false);
}

void ANGGameMode::OnBallHit(ANGBall* InBall, AActor* InOtherActor)
{
	auto Pawn = Cast<ANGPawn>(InOtherActor);
	if (Pawn)
	{
		Pawn->OnBallHit(InBall);

		auto NGGameState = Cast<ANGGameState>(GameState);
		if (NGGameState)
		{
			if (Pawn->GetActorLabel() == TEXT("Paddle_Left"))
				NGGameState->AddScore(0, 1);
			else
				NGGameState->AddScore(1, 0);
		}

	}
	InBall->Destroy();
}

void ANGGameMode::RegisterPawnForAutoReceiveInput(APawn* InPawn)
{
	PendingAutoReceiveInputPawns.Add(InPawn);
}

