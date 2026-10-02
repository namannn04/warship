#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TidesGameMode.generated.h"

/** Boots a zero-asset movement test in an empty Unreal level. */
UCLASS()
class TIDESOFTHEFORSAKEN_API ATidesGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ATidesGameMode();
    virtual void BeginPlay() override;
};
