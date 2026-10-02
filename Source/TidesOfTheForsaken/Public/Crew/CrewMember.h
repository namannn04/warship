#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CrewMember.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UTextRenderComponent;
class AShipActor;

/** Visible blockout worker who walks to jobs in the moving ship's local space. */
UCLASS()
class TIDESOFTHEFORSAKEN_API ACrewMember : public AActor
{
    GENERATED_BODY()

public:
    ACrewMember();
    virtual void Tick(float DeltaSeconds) override;
    void SetShip(AShipActor* Ship);
    void SetRoleLabel(const FString& Label);
    void SetWorkDestination(double LocalX, double LocalY);
    bool HasReachedDestination() const;
    FVector GetShipLocalPosition() const;

private:
    UPROPERTY(VisibleAnywhere, Category="Crew")
    TObjectPtr<USceneComponent> Root;

    UPROPERTY(VisibleAnywhere, Category="Crew")
    TObjectPtr<UStaticMeshComponent> Body;

    UPROPERTY(VisibleAnywhere, Category="Crew")
    TObjectPtr<UStaticMeshComponent> Head;

    UPROPERTY(VisibleAnywhere, Category="Crew")
    TObjectPtr<UTextRenderComponent> RoleText;

    UPROPERTY()
    TObjectPtr<AShipActor> Ship;

    FVector2D DestinationLocal = FVector2D::ZeroVector;
};
