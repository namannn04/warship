#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Crew/CrewJobBoard.h"
#include "ShipCrewComponent.generated.h"

class AShipCannon;
class ACrewMember;
class UShipDamageComponent;

struct FCrewWorker
{
    int Id = 0;
    Tides::Crew::ERole Role = Tides::Crew::ERole::Sailor;
    int JobId = -1;
    float WorkElapsed = 0.f;
    double X = 0.0;
    double Y = 0.0;
};

/** Low-frequency crew simulation: gunners and carpenter claim shared jobs. */
UCLASS(ClassGroup=(Ship), meta=(BlueprintSpawnableComponent))
class TIDESOFTHEFORSAKEN_API UShipCrewComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UShipCrewComponent();
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    void RegisterCannon(AShipCannon* Cannon);
    void RegisterCrewMember(int32 CrewId, ACrewMember* Member);
    void SetWorkEnabled(bool bValue) { bWorkEnabled = bValue; }

    UFUNCTION(BlueprintPure, Category="Ship|Crew")
    int32 GetActiveJobCount() const { return static_cast<int32>(JobBoard.Count()); }

private:
    void UpdateJobs();
    void WorkOneStep(FCrewWorker& Worker, const Tides::Crew::FJob& Job);

    UPROPERTY()
    TArray<TObjectPtr<AShipCannon>> Cannons;

    UPROPERTY()
    TArray<TObjectPtr<ACrewMember>> CrewActors;

    Tides::Crew::FJobBoard JobBoard;
    TArray<FCrewWorker> Workers;
    float TimeAccumulator = 0.f;
    bool bWorkEnabled = true;
};
