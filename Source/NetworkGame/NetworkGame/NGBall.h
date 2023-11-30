#pragma once

#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperSpriteComponent.h"
#include "NGBall.generated.h"

UCLASS(config = Game)
class ANGBall : public APawn
{
	GENERATED_BODY()

public:
	static void Spawn(AActor* InShooter, FVector InVelocity);

	ANGBall();

	virtual void BeginPlay() override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
private:
	UFUNCTION()
	void OnHitCallback(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	UPROPERTY()
	TWeakObjectPtr<AActor> Shooter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = NGBall)
	TObjectPtr<UPaperSpriteComponent> SpriteComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = NGBall)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
};
