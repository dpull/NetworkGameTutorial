#pragma once

#include "NGBall.h"
#include "GameFramework/Character.h"
#include "PaperSpriteComponent.h"
#include "NGPawn.generated.h"

UCLASS(config = Game)
class ANGPawn : public APawn
{
	GENERATED_BODY()

public:
	ANGPawn();

	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnRep_ReplicatedMovement() override;
	virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

	void MoveTarget(float TargetZ);

	UFUNCTION(NetMulticast, Reliable)
	void OnBallHit(ANGBall* Ball);

protected:
	void OnMovementInput(float InScale);
	void OnShootInput();

	UFUNCTION(unreliable, server, WithValidation)
	void ServerMove(float InTimeStamp,float InDeltaTime, const FVector& InMoveDirection);
	void ClientMove(float InDeltaTime, const FVector& InMoveDirection);
	void RealMove(float InDeltaTime, const FVector& InMoveDirection);

	UFUNCTION(reliable, server, WithValidation)
	void ServerShoot();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = NGPawn)
	TObjectPtr<UPaperSpriteComponent> SpriteComponent;

	UPROPERTY(EditAnywhere, Category = NGPawn)
	float Speed;

	UPROPERTY(EditAnywhere, Category = NGPawn)
	FVector BallVelocity;

	float LastServerMoveTimeStamp = 0;
};
