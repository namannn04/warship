#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CaptainCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;
class AShipActor;
class AShipCannon;

/** Third-person captain with direct deck traversal and physical helm handoff. */
UCLASS()
class TIDESOFTHEFORSAKEN_API ACaptainCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ACaptainCharacter();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    void TakeHelm(AShipActor* Ship);
    void OperateCannon(AShipCannon* Cannon);

private:
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);
    void Interact();
    void FireCannon();
    void RaiseSails();
    void ReduceSails();
    void ToggleAnchor();
    void OrderPort();
    void OrderStarboard();
    void ToggleSpyglass();
    AShipActor* GetShipForOrders() const;
    AActor* FindFocusedInteractable() const;

    UPROPERTY(VisibleAnywhere, Category="Camera")
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, Category="Camera")
    TObjectPtr<UCameraComponent> FollowCamera;

    UPROPERTY(VisibleAnywhere, Category="Visual")
    TObjectPtr<UStaticMeshComponent> PrototypeBody;

    UPROPERTY()
    TObjectPtr<AShipActor> SteeredShip;

    UPROPERTY()
    TObjectPtr<AShipCannon> OperatedCannon;

    float SteeringInput = 0.f;
    bool bUsingSpyglass = false;
};
