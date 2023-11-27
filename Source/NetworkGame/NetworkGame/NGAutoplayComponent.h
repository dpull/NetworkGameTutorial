#pragma once

#include "GameFramework/Character.h"
#include "NGAutoplayComponent.generated.h"

UCLASS(config = Game)
class UNGAutoplayComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNGAutoplayComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, Category = NGPawn)
	bool bEnable;
};
