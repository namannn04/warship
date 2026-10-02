#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Combat/NavalAIModel.h"
#include "EnemyShipAIComponent.generated.h"

class AShipActor;
class AShipCannon;

struct FEnemyCannon
{
    TWeakObjectPtr<AShipCannon> Cannon;
    Tides::NavalAI::ESide Side = Tides::NavalAI::ESide::Port;
};

/** Low-frequency ship helm and broadside decisions for the combat prototype. */
UCLASS(ClassGroup=(Ship), meta=(BlueprintSpawnableComponent))
class TIDESOFTHEFORSAKEN_API UEnemyShipAIComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UEnemyShipAIComponent();
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void SetTarget(AShipActor* Ship);
    void RegisterCannon(AShipCannon* Cannon, Tides::NavalAI::ESide Side);

private:
    UPROPERTY()
    TObjectPtr<AShipActor> TargetShip;

    TArray<FEnemyCannon> Cannons;
};
