#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weather/WeatherModel.h"
#include "WeatherDirector.generated.h"

class AShipActor;
class ADirectionalLight;

/** Drives one shared weather state for all ships and the sun. */
UCLASS()
class TIDESOFTHEFORSAKEN_API AWeatherDirector : public AActor
{
    GENERATED_BODY()

public:
    AWeatherDirector();
    virtual void Tick(float DeltaSeconds) override;
    void RegisterShip(AShipActor* Ship);
    void SetSun(ADirectionalLight* Light);

private:
    UPROPERTY()
    TArray<TObjectPtr<AShipActor>> Ships;

    UPROPERTY()
    TObjectPtr<ADirectionalLight> Sun;

    Tides::Weather::FState WeatherState;
};
