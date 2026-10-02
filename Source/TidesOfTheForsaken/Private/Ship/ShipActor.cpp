#include "Ship/ShipActor.h"
#include "Ship/ShipMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AShipActor::AShipActor()
{
    PrimaryActorTick.bCanEverTick = false;

    DeckCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WalkableDeck"));
    SetRootComponent(DeckCollision);
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

    ShipMovement = CreateDefaultSubobject<UShipMovementComponent>(TEXT("ShipMovement"));
}

FVector AShipActor::GetCaptainStartLocation() const
{
    return DeckCollision->GetComponentTransform().TransformPosition(FVector(-650.f, 0.f, 130.f));
}

FVector AShipActor::GetHelmLocation() const
{
    return DeckCollision->GetComponentTransform().TransformPosition(FVector(-850.f, 0.f, 90.f));
}
