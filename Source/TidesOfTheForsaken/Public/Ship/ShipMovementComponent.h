#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ship/SailingModel.h"
#include "ShipMovementComponent.generated.h"

/** Kinematic sailing motion. Deck characters use Unreal's movement base to inherit it. */
UCLASS(ClassGroup=(Ship), meta=(BlueprintSpawnableComponent))
class TIDESOFTHEFORSAKEN_API UShipMovementComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UShipMovementComponent();
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category="Ship|Sailing")
    void SetSailPower(float Value);

    UFUNCTION(BlueprintCallable, Category="Ship|Sailing")
    void SetRudder(float Value);

    UFUNCTION(BlueprintCallable, Category="Ship|Sailing")
    void SetAnchored(bool bValue);

    void SetConditionFactors(float SailFactor, float RudderFactor, float WaterLevel);

    UFUNCTION(BlueprintPure, Category="Ship|Sailing")
    float GetSpeedCmPerSecond() const { return SpeedCmPerSecond; }

    UFUNCTION(BlueprintPure, Category="Ship|Sailing")
    float GetSailPower() const { return SailPower; }

    UFUNCTION(BlueprintPure, Category="Ship|Sailing")
    float GetRudder() const { return Rudder; }

    UFUNCTION(BlueprintPure, Category="Ship|Sailing")
    bool IsAnchored() const { return bAnchored; }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ship|Sailing", meta=(ClampMin="0"))
    float MaximumSpeedCmPerSecond = 450.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ship|Sailing", meta=(ClampMin="0"))
    float AccelerationCmPerSecondSquared = 35.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ship|Sailing", meta=(ClampMin="0"))
    float DecelerationCmPerSecondSquared = 55.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ship|Sailing", meta=(ClampMin="0"))
    float MaximumTurnDegreesPerSecond = 8.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ship|Sailing")
    FVector WindDirection = FVector(1.f, 0.3f, 0.f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ship|Waves", meta=(ClampMin="0"))
    float WaveHeightCm = 22.f;

private:
    float SailPower = 0.45f;
    float Rudder = 0.f;
    float SpeedCmPerSecond = 0.f;
    bool bAnchored = false;
    float BaseWaterlineZ = 0.f;
    Tides::Sailing::FState SailingState;
    float SailCondition = 1.f;
    float RudderCondition = 1.f;
    float WaterLevel = 0.f;
};
