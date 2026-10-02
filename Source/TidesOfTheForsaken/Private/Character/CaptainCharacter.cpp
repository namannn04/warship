#include "Character/CaptainCharacter.h"
#include "Ship/ShipActor.h"
#include "Ship/ShipMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
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

AShipActor* ACaptainCharacter::FindNearbyShip() const
{
    TArray<AActor*> Ships;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShipActor::StaticClass(), Ships);
    for (AActor* Actor : Ships)
    {
        AShipActor* Ship = Cast<AShipActor>(Actor);
        if (Ship && FVector::Dist(GetActorLocation(), Ship->GetHelmLocation()) < 240.f) return Ship;
    }
    return nullptr;
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
    if (AShipActor* Ship = FindNearbyShip())
    {
        SteeredShip = Ship;
        Ship->SetCaptainSteering(true);
        GetCharacterMovement()->StopMovementImmediately();
        GetCharacterMovement()->SetMovementMode(MOVE_None);
        SetActorLocation(Ship->GetHelmLocation());
    }
}
