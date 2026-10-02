#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TidesGameMode.generated.h"

class AShipActor;
class AController;

/** Boots the blockout naval combat encounter in an empty Unreal level. */
UCLASS()
class TIDESOFTHEFORSAKEN_API ATidesGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ATidesGameMode();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void RestartPlayer(AController* NewPlayer) override;

    AShipActor* GetEnemyShip() const { return EnemyShip; }

private:
    void PlaceCaptain(AController* Controller) const;

    UPROPERTY()
    TObjectPtr<AShipActor> PrototypeShip;

    UPROPERTY()
    TObjectPtr<AShipActor> EnemyShip;

    bool bBattleEnded = false;
    bool bPlayerVictory = false;
};
