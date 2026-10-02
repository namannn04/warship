#include "Ship/ShipActor.h"
#include "Ship/ShipMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AShipActor::AShipActor()
{
    PrimaryActorTick.bCanEverTick = true;

    ShipRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ShipRoot"));
    SetRootComponent(ShipRoot);
    DeckCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WalkableDeck"));
    DeckCollision->SetupAttachment(ShipRoot);
    DeckCollision->SetBoxExtent(FVector(1200.f, 330.f, 35.f));
    DeckCollision->SetRelativeLocation(FVector(0.f, 0.f, 220.f));
    DeckCollision->SetCollisionProfileName(TEXT("BlockAll"));
    DeckCollision->SetCanEverAffectNavigation(false);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    HullVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HullVisual"));
    HullVisual->SetupAttachment(DeckCollision);
    HullVisual->SetRelativeLocation(FVector(0.f, 0.f, -105.f));
    HullVisual->SetRelativeScale3D(FVector(24.f, 7.f, 2.1f));
    HullVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    if (Cube.Succeeded()) HullVisual->SetStaticMesh(Cube.Object);

    MastVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MastVisual"));
    MastVisual->SetupAttachment(DeckCollision);
    MastVisual->SetRelativeLocation(FVector(100.f, 0.f, 550.f));
    MastVisual->SetRelativeScale3D(FVector(0.5f, 0.5f, 11.f));
    MastVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    if (Cube.Succeeded()) MastVisual->SetStaticMesh(Cube.Object);

    HelmVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HelmVisual"));
    HelmVisual->SetupAttachment(DeckCollision);
    HelmVisual->SetRelativeLocation(FVector(-850.f, 0.f, 95.f));
    HelmVisual->SetRelativeScale3D(FVector(0.15f, 1.2f, 1.2f));
    HelmVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    if (Cube.Succeeded()) HelmVisual->SetStaticMesh(Cube.Object);

    ShipMovement = CreateDefaultSubobject<UShipMovementComponent>(TEXT("ShipMovement"));
}

FVector AShipActor::GetCaptainStartLocation() const
{
    return DeckCollision->GetComponentTransform().TransformPosition(FVector(-650.f, 0.f, 130.f));
}

FVector AShipActor::GetHelmLocation() const
{
    return DeckCollision->GetComponentTransform().TransformPosition(FVector(-850.f, 0.f, 135.f));
}

void AShipActor::SetCaptainSteering(bool bSteering)
{
    bCaptainSteering = bSteering;
    if (!bSteering)
    {
        HeldHeading = GetActorRotation().Yaw;
    }
}

void AShipActor::SetHelmRudder(float Value)
{
    if (bCaptainSteering) ShipMovement->SetRudder(Value);
}

void AShipActor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (!bCaptainSteering)
    {
        const float Error = FMath::FindDeltaAngleDegrees(GetActorRotation().Yaw, HeldHeading);
        ShipMovement->SetRudder(FMath::Clamp(Error / 25.f, -1.f, 1.f));
    }
}
