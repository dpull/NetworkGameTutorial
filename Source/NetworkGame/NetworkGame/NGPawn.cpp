#include "NGPawn.h"
#include "EngineUtils.h"
#include "ToolBuilderUtil.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

static AActor* FindActorByLabel(UWorld* World, const FString& ActorName)
{
	AActor* FoundActor = nullptr;
	for (TActorIterator<AActor> ActorItr(World); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetActorLabel() == ActorName)
		{
			FoundActor = *ActorItr;
			break;
		}
	}
	return FoundActor;
}

ANGPawn::ANGPawn()
{
	Speed = 600;
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	SpriteComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	AutoPlay = CreateDefaultSubobject<UNGAutoplayComponent>(TEXT("AutoPlay"));
}

void ANGPawn::BeginPlay()
{
	Super::BeginPlay();

	if (GIsClient && (GetLocalRole() == ENetRole::ROLE_AutonomousProxy || GetLocalRole() == ENetRole::ROLE_Authority))
	{
		auto PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController)
		{
			auto Camera = FindActorByLabel(GetWorld(), TEXT("CameraActor"));
			if (Camera)
				PlayerController->SetViewTargetWithBlend(Camera);
		}
	}
}

void ANGPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("VerticalMovementAxis"), this, &ANGPawn::Move);
}

void ANGPawn::MoveTarget(float TargetZ)
{
	auto Current = GetActorLocation();
	auto Target = Current;
	Target.Z = TargetZ;
	Target = FMath::VInterpTo(Current, Target, GetWorld()->DeltaTimeSeconds, Speed);
	SetActorLocation(Target, true);
}

void ANGPawn::Move(float InScale)
{
	const auto Z = GetWorld()->DeltaTimeSeconds * Speed * InScale;
	AddActorWorldOffset(FVector(0, 0, Z), true);
}
