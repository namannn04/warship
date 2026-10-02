#include "Ship/ShipActor.h"
#include "Ship/ShipMovementComponent.h"
#include "Crew/ShipCommandComponent.h"
#include "Ship/ShipDamageComponent.h"
#include "Ship/ShipInventoryComponent.h"
#include "Ship/ShipFireComponent.h"
#include "Crew/ShipCrewComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "UObject/ConstructorHelpers.h"

AShipActor::AShipActor()
{
    PrimaryActorTick.bCanEverTick = false;

    ShipRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ShipRoot"));
    SetRootComponent(ShipRoot);
    DeckOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("DeckOrigin"));
    DeckOrigin->SetupAttachment(ShipRoot);
    DeckOrigin->SetRelativeLocation(FVector(0.f, 0.f, 220.f));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    // Each piece is a separate moving collision base. The gap in the weather deck
    // is an actual opening above the stairs, not a visual decal.
    const auto AddPiece = [this](const TCHAR* Name, const FVector& Center, const FVector& Size)
    {
        UStaticMeshComponent* Piece = CreateDefaultSubobject<UStaticMeshComponent>(Name);
        Piece->SetupAttachment(DeckOrigin);
        Piece->SetMobility(EComponentMobility::Movable);
        Piece->SetRelativeLocation(Center);
        Piece->SetRelativeScale3D(Size / 100.f);
        Piece->SetCollisionProfileName(TEXT("BlockAll"));
        Piece->SetCanEverAffectNavigation(false);
        if (Cube.Succeeded()) Piece->SetStaticMesh(Cube.Object);
        StructurePieces.Add(Piece);
    };

    // Weather deck: centre opening runs from x=-400 to x=400, y=-130 to y=130.
    AddPiece(TEXT("WeatherPort"), FVector(0.f, -230.f, 0.f), FVector(2400.f, 200.f, 70.f));
    AddPiece(TEXT("WeatherStarboard"), FVector(0.f, 230.f, 0.f), FVector(2400.f, 200.f, 70.f));
    AddPiece(TEXT("WeatherFore"), FVector(800.f, 0.f, 0.f), FVector(800.f, 260.f, 70.f));
    AddPiece(TEXT("WeatherAft"), FVector(-800.f, 0.f, 0.f), FVector(800.f, 260.f, 70.f));
    // Gun-deck hatch sits farther forward, so the two stair flights do not overlap.
    AddPiece(TEXT("GunPort"), FVector(0.f, -230.f, -300.f), FVector(2400.f, 200.f, 70.f));
    AddPiece(TEXT("GunStarboard"), FVector(0.f, 230.f, -300.f), FVector(2400.f, 200.f, 70.f));
    AddPiece(TEXT("GunAft"), FVector(-375.f, 0.f, -300.f), FVector(1650.f, 260.f, 70.f));
    AddPiece(TEXT("GunFore"), FVector(1125.f, 0.f, -300.f), FVector(150.f, 260.f, 70.f));
    AddPiece(TEXT("HoldFloor"), FVector(0.f, 0.f, -600.f), FVector(2400.f, 660.f, 70.f));

    // Ten 30 cm risers descend 300 cm over eight metres. CharacterMovement's
    // normal step-up can traverse them without a teleport or a movement mode swap.
    for (int32 Index = 0; Index < 10; ++Index)
    {
        const FName StepName(*FString::Printf(TEXT("StairStep_%02d"), Index));
        const FVector Center(-360.f + Index * 80.f, 0.f, -10.f - Index * 30.f);
        UStaticMeshComponent* Step = CreateDefaultSubobject<UStaticMeshComponent>(StepName);
        Step->SetupAttachment(DeckOrigin);
        Step->SetMobility(EComponentMobility::Movable);
        Step->SetRelativeLocation(Center);
        Step->SetRelativeScale3D(FVector(0.8f, 2.6f, 0.3f));
        Step->SetCollisionProfileName(TEXT("BlockAll"));
        Step->SetCanEverAffectNavigation(false);
        if (Cube.Succeeded()) Step->SetStaticMesh(Cube.Object);
        StructurePieces.Add(Step);
    }

    // A second ten-step flight reaches the hold from the forward gun deck.
    for (int32 Index = 0; Index < 10; ++Index)
    {
        const FName StepName(*FString::Printf(TEXT("HoldStair_%02d"), Index));
        const FVector Center(480.f + Index * 60.f, 0.f, -310.f - Index * 30.f);
        UStaticMeshComponent* Step = CreateDefaultSubobject<UStaticMeshComponent>(StepName);
        Step->SetupAttachment(DeckOrigin);
        Step->SetMobility(EComponentMobility::Movable);
        Step->SetRelativeLocation(Center);
        Step->SetRelativeScale3D(FVector(0.6f, 2.6f, 0.3f));
        Step->SetCollisionProfileName(TEXT("BlockAll"));
        Step->SetCanEverAffectNavigation(false);
        if (Cube.Succeeded()) Step->SetStaticMesh(Cube.Object);
        StructurePieces.Add(Step);
    }

    // The hollow hull encloses both interior levels without filling them.
    AddPiece(TEXT("HullPort"), FVector(0.f, -345.f, -265.f), FVector(2400.f, 30.f, 600.f));
    AddPiece(TEXT("HullStarboard"), FVector(0.f, 345.f, -265.f), FVector(2400.f, 30.f, 600.f));
    AddPiece(TEXT("HullBow"), FVector(1215.f, 0.f, -265.f), FVector(30.f, 690.f, 600.f));
    AddPiece(TEXT("HullStern"), FVector(-1215.f, 0.f, -265.f), FVector(30.f, 690.f, 600.f));

    // Supply crates line the hold walls while the central walking route stays open.
    for (int32 Index = 0; Index < 6; ++Index)
    {
        const FName CrateName(*FString::Printf(TEXT("SupplyCrate_%02d"), Index));
        const float X = -950.f + (Index / 2) * 600.f;
        const float Y = Index % 2 == 0 ? -225.f : 225.f;
        UStaticMeshComponent* Crate = CreateDefaultSubobject<UStaticMeshComponent>(CrateName);
        Crate->SetupAttachment(DeckOrigin);
        Crate->SetMobility(EComponentMobility::Movable);
        Crate->SetRelativeLocation(FVector(X, Y, -510.f));
        Crate->SetRelativeScale3D(FVector(0.9f, 0.9f, 0.9f));
        Crate->SetCollisionProfileName(TEXT("BlockAll"));
        Crate->SetCanEverAffectNavigation(false);
        if (Cube.Succeeded()) Crate->SetStaticMesh(Cube.Object);
        StructurePieces.Add(Crate);
    }

    MastVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MastVisual"));
    MastVisual->SetupAttachment(DeckOrigin);
    MastVisual->SetMobility(EComponentMobility::Movable);
    MastVisual->SetRelativeLocation(FVector(650.f, 0.f, 550.f));
    MastVisual->SetRelativeScale3D(FVector(0.5f, 0.5f, 11.f));
    MastVisual->SetCollisionProfileName(TEXT("BlockAll"));
    if (Cube.Succeeded()) MastVisual->SetStaticMesh(Cube.Object);

    ShipMovement = CreateDefaultSubobject<UShipMovementComponent>(TEXT("ShipMovement"));
    ShipCommands = CreateDefaultSubobject<UShipCommandComponent>(TEXT("ShipCommands"));
    ShipDamage = CreateDefaultSubobject<UShipDamageComponent>(TEXT("ShipDamage"));
    ShipInventory = CreateDefaultSubobject<UShipInventoryComponent>(TEXT("ShipInventory"));
    ShipCrew = CreateDefaultSubobject<UShipCrewComponent>(TEXT("ShipCrew"));
    ShipFire = CreateDefaultSubobject<UShipFireComponent>(TEXT("ShipFire"));

    const auto AddFireLight = [this](const TCHAR* Name, const FVector& Position)
    {
        UPointLightComponent* Light = CreateDefaultSubobject<UPointLightComponent>(Name);
        Light->SetupAttachment(DeckOrigin);
        Light->SetRelativeLocation(Position);
        Light->SetLightColor(FLinearColor(1.f, 0.25f, 0.02f));
        Light->SetAttenuationRadius(450.f);
        Light->SetIntensity(0.f);
        return Light;
    };
    DeckFireLight = AddFireLight(TEXT("DeckFireLight"), FVector(0.f, -180.f, 100.f));
    SailFireLight = AddFireLight(TEXT("SailFireLight"), FVector(650.f, 0.f, 650.f));
    HoldFireLight = AddFireLight(TEXT("HoldFireLight"), FVector(0.f, 0.f, -460.f));
}

void AShipActor::SetFireVisuals(float DeckHeat, float SailHeat, float HoldHeat)
{
    DeckFireLight->SetIntensity(DeckHeat * 35.f);
    SailFireLight->SetIntensity(SailHeat * 35.f);
    HoldFireLight->SetIntensity(HoldHeat * 35.f);
}

FVector AShipActor::GetCaptainStartLocation() const
{
    return DeckOrigin->GetComponentTransform().TransformPosition(FVector(-650.f, 0.f, 130.f));
}

FVector AShipActor::GetHelmLocation() const
{
    return DeckOrigin->GetComponentTransform().TransformPosition(FVector(-850.f, 0.f, 135.f));
}

FVector AShipActor::GetCannonLocation(float AlongShip, bool bPort) const
{
    return DeckOrigin->GetComponentTransform().TransformPosition(
        FVector(AlongShip, bPort ? -245.f : 245.f, -230.f));
}

FVector AShipActor::GetRepairStationLocation() const
{
    return DeckOrigin->GetComponentTransform().TransformPosition(FVector(-900.f, 0.f, -195.f));
}

FVector AShipActor::GetGunDeckCrewLocation(float AlongShip, float AcrossShip) const
{
    return DeckOrigin->GetComponentTransform().TransformPosition(FVector(AlongShip, AcrossShip, -190.f));
}

FVector AShipActor::GetSupplyLedgerLocation() const
{
    return DeckOrigin->GetComponentTransform().TransformPosition(FVector(-950.f, 0.f, -505.f));
}

void AShipActor::SetCaptainSteering(bool bSteering)
{
    ShipCommands->SetCaptainAtHelm(bSteering);
}

void AShipActor::SetHelmRudder(float Value)
{
    if (ShipCommands->IsCaptainAtHelm()) ShipMovement->SetRudder(Value);
}

bool AShipActor::IsCaptainSteering() const
{
    return ShipCommands->IsCaptainAtHelm();
}
