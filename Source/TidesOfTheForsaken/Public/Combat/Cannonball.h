#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cannonball.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;
class AShipActor;

/** Physical shot; impact damage can be added per ship section. */
UCLASS()
class TIDESOFTHEFORSAKEN_API ACannonball : public AActor
{
    GENERATED_BODY()

public:
    ACannonball();
    void IgnoreShip(AShipActor* Ship);

private:
    UFUNCTION()
    void OnImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

    UPROPERTY(VisibleAnywhere, Category="Projectile")
    TObjectPtr<USphereComponent> Collision;

    UPROPERTY(VisibleAnywhere, Category="Projectile")
    TObjectPtr<UStaticMeshComponent> Visual;

    UPROPERTY(VisibleAnywhere, Category="Projectile")
    TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

    UPROPERTY()
    TObjectPtr<AShipActor> SourceShip;
};
