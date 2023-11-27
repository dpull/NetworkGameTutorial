#include "NGAutoplayComponent.h"

#include "NGGameMode.h"
#include "NGPawn.h"
#include "Engine/World.h"
#include "GameFramework/ProjectileMovementComponent.h"

UNGAutoplayComponent::UNGAutoplayComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bEnable = false;
}

void UNGAutoplayComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!bEnable)
		return;

	auto GameMode = GetWorld()->GetAuthGameMode<ANGGameMode>();
	if (!GameMode)
		return;

	auto Ball = GameMode->GetBall();
	if (!Ball)
		return;

	auto MovementComponent = Ball->GetComponentByClass<UProjectileMovementComponent>();
	if (!MovementComponent)
		return;

	if (MovementComponent->Velocity.X > 0)
		return;

	auto Pawn = Cast<ANGPawn>(GetOwner());
	if (!Pawn)
		return;

	auto Location = Ball->GetActorLocation();
	Pawn->MoveTarget(Location.Z);
}
