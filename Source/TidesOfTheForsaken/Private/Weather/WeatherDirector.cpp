#include "Weather/WeatherDirector.h"
#include "Ship/ShipActor.h"
#include "Ship/ShipMovementComponent.h"
#include "Ship/ShipFireComponent.h"
#include "Engine/DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"

AWeatherDirector::AWeatherDirector()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AWeatherDirector::RegisterShip(AShipActor* Ship)
{
    if (IsValid(Ship)) Ships.AddUnique(Ship);
}

void AWeatherDirector::SetSun(ADirectionalLight* Light)
{
    Sun = Light;
}

void AWeatherDirector::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    const double CycleSeconds = FMath::Fmod(WeatherState.ElapsedSeconds, 240.0);
    WeatherState.TargetStorm = CycleSeconds >= 90.0 && CycleSeconds < 180.0 ? 1.0 : 0.0;
    Tides::Weather::Advance(WeatherState, DeltaSeconds);

    for (AShipActor* Ship : Ships)
    {
        if (!IsValid(Ship)) continue;
        Ship->GetShipMovement()->SetWeather(
            static_cast<float>(Tides::Weather::WindHeadingDegrees(WeatherState)),
            static_cast<float>(Tides::Weather::WaveHeightCm(WeatherState)),
            static_cast<float>(Tides::Weather::WindSpeedFactor(WeatherState)));
        Ship->GetShipFire()->SetWeather(static_cast<float>(WeatherState.Storm),
            static_cast<float>(WeatherState.Storm));
    }
    if (IsValid(Sun))
    {
        const float Solar = static_cast<float>(Tides::Weather::SunFactor(WeatherState));
        Sun->GetLightComponent()->SetIntensity(0.1f + Solar * 8.f);
        const float SolarAngle = static_cast<float>((WeatherState.Hours - 6.0) * 15.0);
        Sun->SetActorRotation(FRotator(-SolarAngle, -30.f, 0.f));
    }
}
