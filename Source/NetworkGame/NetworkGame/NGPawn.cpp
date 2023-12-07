#include "NGPawn.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "NGBall.h"
#include "NGGameMode.h"
#include "TimerManager.h"
#include "ToolBuilderUtil.h"
#include "Components/InputComponent.h"
#include "Engine/NetDriver.h"
#include "Engine/World.h"
#include "GameFramework/MovementComponent.h"
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
}

void ANGPawn::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	if (AutoPossessPlayer != EAutoReceiveInput::Disabled)
	{
		auto GameMode = GetWorld()->GetAuthGameMode<ANGGameMode>();
		if (GameMode)
		{
			GameMode->RegisterPawnForAutoReceiveInput(this);
		}
	}
}

void ANGPawn::BeginPlay()
{
	Super::BeginPlay();

	if (GetNetMode() == NM_Standalone || GetLocalRole() == ROLE_AutonomousProxy)
	{
		auto PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController)
		{
			auto Camera = FindActorByLabel(GetWorld(), TEXT("CameraActor"));
			if (Camera)
				PlayerController->SetViewTargetWithBlend(Camera);
		}
	}

	UE_LOG(LogNG, Warning, TEXT("%s, NetMode=%d bReplicateMovement=%d"), *GetActorLabel(), GetNetMode(), IsReplicatingMovement());
}

void ANGPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("VerticalMovementAxis"), this, &ANGPawn::OnMovementInput);
	PlayerInputComponent->BindKey(EKeys::SpaceBar, IE_Pressed, this, &ANGPawn::OnShootInput);
}

void ANGPawn::OnRep_ReplicatedMovement()
{
	const FRepMovement& LocalRepMovement = GetReplicatedMovement();
	DrawDebugCapsule(GetWorld(), LocalRepMovement.Location, GetSimpleCollisionHalfHeight(), GetSimpleCollisionRadius(), LocalRepMovement.Rotation.Quaternion(), FColor(100, 255, 100), false, 1.f);
	Super::OnRep_ReplicatedMovement();
}

void ANGPawn::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	auto LocalRole = GetLocalRole();
	if (LocalRole == ROLE_AutonomousProxy)
	{
		auto InputVector = Internal_ConsumeMovementInputVector();
		ClientMove(DeltaTime, InputVector);
	}
}

void ANGPawn::MoveTarget(float TargetZ)
{
	if (GetLocalRole() != ROLE_AutonomousProxy)
		return;

	auto Current = GetActorLocation();
	auto Diff = TargetZ - Current.Z;
	if (Diff == 0)
		return;

	OnMovementInput(Diff > 0 ? 1 : -1);
}

void ANGPawn::OnBallHit_Implementation(ANGBall* Ball)
{
	SpriteComponent->SetSpriteColor(FLinearColor::Black);

	FTimerHandle DummyHandle;
	GetWorld()->GetTimerManager().SetTimer(
		DummyHandle, [this]() {
			this->SpriteComponent->SetSpriteColor(FLinearColor::White);
		},
		0.2f, false);
}

void ANGPawn::OnMovementInput(float InScale)
{
	AddMovementInput(FVector(0, 0, 1), InScale);
}

void ANGPawn::OnShootInput()
{
	ServerShoot();
}

void ANGPawn::ServerMove_Implementation(float InTimeStamp,float InDeltaTime, const FVector& InMoveDirection)
{
	if (LastServerMoveTimeStamp > InTimeStamp)
		return;
	LastServerMoveTimeStamp = InDeltaTime;
	RealMove(InDeltaTime, InMoveDirection);
}

bool ANGPawn::ServerMove_Validate(float InTimeStamp,float InDeltaTime, const FVector& InMoveDirection)
{
	return true;
}

void ANGPawn::ClientMove(float InDeltaTime, const FVector& InMoveDirection)
{
	if (InMoveDirection.IsZero())
		return;

	RealMove(InDeltaTime, InMoveDirection);
	ServerMove(GetWorld()->TimeSeconds, InDeltaTime, InMoveDirection);
}

void ANGPawn::RealMove(float InDeltaTime, const FVector& InMoveDirection)
{
	auto DeltaLocation = InMoveDirection * (Speed * InDeltaTime);
	AddActorWorldOffset(DeltaLocation, true);
}

void ANGPawn::ServerShoot_Implementation()
{
	ANGBall::Spawn(this, BallVelocity);
}

bool ANGPawn::ServerShoot_Validate()
{
	return true;
}
