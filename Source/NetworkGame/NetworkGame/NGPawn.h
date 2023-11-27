#pragma once

#include "NGAutoplayComponent.h"
#include "GameFramework/Character.h"
#include "PaperSpriteComponent.h"
#include "NGPawn.generated.h"

UCLASS(config = Game)
class ANGPawn : public APawn
{
	GENERATED_BODY()

public:
	ANGPawn();

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveTarget(float TargetZ);

protected:
	void Move(float InScale);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = NGPawn)
	TObjectPtr<UPaperSpriteComponent> SpriteComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = NGPawn)
	TObjectPtr<UNGAutoplayComponent> AutoPlay;

	UPROPERTY(EditAnywhere, Category = NGPawn)
	float Speed;
};
