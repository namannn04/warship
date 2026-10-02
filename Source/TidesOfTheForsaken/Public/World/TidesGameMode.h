#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TidesGameMode.generated.h"

class AShipActor;
class AController;

/** Boots a zero-asset movement test in an empty Unreal level. */
UCLASS()
class TIDESOFTHEFORSAKEN_API ATidesGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ATidesGameMode();
    virtual void BeginPlay() override;
    virtual void RestartPlayer(AController* NewPlayer) override;

private:
    void PlaceCaptain(AController* Controller) const;

    UPROPERTY()
    TObjectPtr<AShipActor> PrototypeShip;
};
