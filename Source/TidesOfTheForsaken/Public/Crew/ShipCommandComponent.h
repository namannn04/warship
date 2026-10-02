#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShipCommandComponent.generated.h"

class UShipMovementComponent;

/** High-level orders shared by the captain and the helmsman. */
UCLASS(ClassGroup=(Ship), meta=(BlueprintSpawnableComponent))
class TIDESOFTHEFORSAKEN_API UShipCommandComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UShipCommandComponent();
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category="Ship|Orders")
    void SetCaptainAtHelm(bool bValue);

    UFUNCTION(BlueprintCallable, Category="Ship|Orders")
    void OrderSailPower(float Power);

    UFUNCTION(BlueprintCallable, Category="Ship|Orders")
    void OrderTurn(float Degrees);

    UFUNCTION(BlueprintCallable, Category="Ship|Orders")
    void OrderHoldHeading();

    UFUNCTION(BlueprintCallable, Category="Ship|Orders")
    void OrderAnchorToggle();

    UFUNCTION(BlueprintPure, Category="Ship|Orders")
    bool IsCaptainAtHelm() const { return bCaptainAtHelm; }

    UFUNCTION(BlueprintPure, Category="Ship|Orders")
    float GetOrderedHeading() const { return OrderedHeading; }

private:
    UPROPERTY()
    TObjectPtr<UShipMovementComponent> Movement;

    bool bCaptainAtHelm = false;
    float OrderedHeading = 0.f;
};
