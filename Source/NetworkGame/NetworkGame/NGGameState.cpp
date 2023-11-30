#include "NGGameState.h"

#include "NGHud.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Net/UnrealNetwork.h"

void ANGGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
		
	DOREPLIFETIME(ANGGameState, ScoreLeft);
	DOREPLIFETIME(ANGGameState, ScoreRight);
}

void ANGGameState::AddScore(int32 InAddLeft, int32 InAddRight)
{
	ScoreLeft += InAddLeft;
	ScoreRight += InAddRight;
}

void ANGGameState::OnRep_Score()
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController)
		return;
	
	auto HUD = Cast<ANGHud>(PlayerController->GetHUD());
	if (!HUD)
		return;
	
	HUD->UpdateScore(ScoreLeft, ScoreRight);
}
