#include "NGBall.h"
#include "NGGameMode.h"
#include "NGPawn.h"
#include "PaperSprite.h"
#include "Engine/Font.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

void ANGBall::Spawn(AActor* InShooter, FVector InVelocity)
{
	auto Ball = InShooter->GetWorld()->SpawnActor<ANGBall>();
	if (!Ball)
		return;

	auto Location = InShooter->GetActorLocation();
	Location.X += InVelocity.X > 0 ? 50 : -50;
	Ball->SetActorLocation(Location);
	Ball->Shooter = InShooter;
	Ball->ProjectileMovement->Velocity = InVelocity;
}

ANGBall::ANGBall()
{
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite(TEXT("/Game/Sprites/Ball_Sprite"));  

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	SpriteComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SpriteComponent->SetSprite(Sprite.Object);
	SpriteComponent->TranslucencySortPriority = 2;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 1;
	ProjectileMovement->Friction = 0;
}

void ANGBall::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() != ROLE_Authority)
		return;
	
	auto PrimComponent = GetComponentByClass<UPrimitiveComponent>();
	if (PrimComponent)
	{
		PrimComponent->OnComponentHit.AddDynamic(this, &ANGBall::OnHitCallback);
	}
}

void ANGBall::NotifyActorEndOverlap(AActor* OtherActor)
{
 	Super::NotifyActorEndOverlap(OtherActor);
	if (GetLocalRole() != ROLE_Authority)
		return;
	
	auto GameMode = GetWorld()->GetAuthGameMode<ANGGameMode>();
	if (GameMode)
	{
		GameMode->OnBallOverlap(this, OtherActor);
	}
}

void ANGBall::OnHitCallback(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto GameMode = GetWorld()->GetAuthGameMode<ANGGameMode>();
	if (GameMode)
	{
		GameMode->OnBallHit(this, OtherActor);
	}
}
