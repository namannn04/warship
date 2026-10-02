#include "Character/CaptainCharacter.h"
#include "Ship/ShipActor.h"
#include "Ship/ShipMovementComponent.h"
#include "Interaction/ShipInteractable.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"

ACaptainCharacter::ACaptainCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    GetCapsuleComponent()->InitCapsuleSize(42.f, 88.f);
    GetCharacterMovement()->MaxWalkSpeed = 420.f;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
    bUseControllerRotationYaw = false;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 380.f;
    CameraBoom->bUsePawnControlRotation = true;
    CameraBoom->bDoCollisionTest = true;
    CameraBoom->CameraLagSpeed = 7.f;
    CameraBoom->bEnableCameraLag = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    PrototypeBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PrototypeBody"));
    PrototypeBody->SetupAttachment(GetCapsuleComponent());
    PrototypeBody->SetRelativeScale3D(FVector(0.65f, 0.45f, 1.65f));
    PrototypeBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (Cube.Succeeded()) PrototypeBody->SetStaticMesh(Cube.Object);
}

void ACaptainCharacter::BeginPlay()
{
    Super::BeginPlay();
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        PC->bShowMouseCursor = false;
        PC->SetInputMode(FInputModeGameOnly());
    }
}

void ACaptainCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (!SteeredShip)
    {
        if (AActor* Focused = FindFocusedInteractable())
        {
            const IShipInteractable* Target = Cast<IShipInteractable>(Focused);
            if (Target && GEngine)
            {
                GEngine->AddOnScreenDebugMessage(101, 0.f, FColor::White,
                    FString::Printf(TEXT("[E] %s"), *Target->GetInteractionText().ToString()));
            }
        }
    }
    if (SteeredShip)
    {
        SetActorLocation(SteeredShip->GetHelmLocation());
        SetActorRotation(SteeredShip->GetActorRotation());
        SteeredShip->SetHelmRudder(SteeringInput);
    }
}

void ACaptainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACaptainCharacter::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACaptainCharacter::MoveRight);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ACaptainCharacter::Turn);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ACaptainCharacter::LookUp);
    PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &ACaptainCharacter::Interact);
}

void ACaptainCharacter::MoveForward(float Value)
{
    if (SteeredShip)
    {
        if (!FMath::IsNearlyZero(Value))
        {
            UShipMovementComponent* Movement = SteeredShip->GetShipMovement();
            Movement->SetSailPower(Movement->GetSailPower() + Value * GetWorld()->GetDeltaSeconds() * 0.4f);
        }
        return;
    }
    if (Controller && !FMath::IsNearlyZero(Value))
    {
        const FRotator Yaw(0.f, Controller->GetControlRotation().Yaw, 0.f);
        AddMovementInput(FRotationMatrix(Yaw).GetUnitAxis(EAxis::X), Value);
    }
}

void ACaptainCharacter::MoveRight(float Value)
{
    if (SteeredShip)
    {
        SteeringInput = Value;
        return;
    }
    if (Controller && !FMath::IsNearlyZero(Value))
    {
        const FRotator Yaw(0.f, Controller->GetControlRotation().Yaw, 0.f);
        AddMovementInput(FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y), Value);
    }
}

void ACaptainCharacter::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void ACaptainCharacter::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}

AActor* ACaptainCharacter::FindFocusedInteractable() const
{
    if (!FollowCamera || !GetWorld()) return nullptr;
    const FVector Start = FollowCamera->GetComponentLocation();
    const FVector End = Start + FollowCamera->GetForwardVector() * 500.f;
    FHitResult Hit;
    FCollisionQueryParams Query(SCENE_QUERY_STAT(CaptainInteraction), false, this);
    if (!GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Query)) return nullptr;
    AActor* TargetActor = Hit.GetActor();
    const IShipInteractable* Target = Cast<IShipInteractable>(TargetActor);
    return Target && Target->CanInteract(this) ? TargetActor : nullptr;
}

void ACaptainCharacter::TakeHelm(AShipActor* Ship)
{
    if (!IsValid(Ship) || SteeredShip) return;
    SteeredShip = Ship;
    Ship->SetCaptainSteering(true);
    GetCharacterMovement()->StopMovementImmediately();
    GetCharacterMovement()->SetMovementMode(MOVE_None);
    SetActorLocation(Ship->GetHelmLocation());
}

void ACaptainCharacter::Interact()
{
    if (SteeredShip)
    {
        SteeredShip->SetCaptainSteering(false);
        SteeredShip = nullptr;
        SteeringInput = 0.f;
        GetCharacterMovement()->SetMovementMode(MOVE_Walking);
        return;
    }
    if (AActor* Focused = FindFocusedInteractable())
    {
        if (IShipInteractable* Target = Cast<IShipInteractable>(Focused)) Target->Interact(this);
    }
}
