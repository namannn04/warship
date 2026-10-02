#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CaptainCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;
class AShipActor;

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

private:
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);
    void Interact();
    AActor* FindFocusedInteractable() const;

    UPROPERTY(VisibleAnywhere, Category="Camera")
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, Category="Camera")
    TObjectPtr<UCameraComponent> FollowCamera;

    UPROPERTY(VisibleAnywhere, Category="Visual")
    TObjectPtr<UStaticMeshComponent> PrototypeBody;

    UPROPERTY()
    TObjectPtr<AShipActor> SteeredShip;

    float SteeringInput = 0.f;
};
