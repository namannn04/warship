#include "Crew/CrewMember.h"
#include "Ship/ShipActor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "UObject/ConstructorHelpers.h"

ACrewMember::ACrewMember()
{
    PrimaryActorTick.bCanEverTick = true;
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);
    SetActorEnableCollision(false);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
    Body->SetupAttachment(Root);
    Body->SetRelativeScale3D(FVector(0.45f, 0.35f, 1.5f));
    Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    if (Cube.Succeeded()) Body->SetStaticMesh(Cube.Object);

    Head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
    Head->SetupAttachment(Root);
    Head->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
    Head->SetRelativeScale3D(FVector(0.35f));
    Head->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    if (Sphere.Succeeded()) Head->SetStaticMesh(Sphere.Object);

    RoleText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("RoleText"));
    RoleText->SetupAttachment(Root);
    RoleText->SetRelativeLocation(FVector(0.f, 0.f, 140.f));
    RoleText->SetHorizontalAlignment(EHTA_Center);
    RoleText->SetWorldSize(24.f);
}

void ACrewMember::SetShip(AShipActor* InShip)
{
    Ship = InShip;
    if (Ship)
    {
        AttachToActor(Ship, FAttachmentTransformRules::KeepWorldTransform);
        const FVector Local = GetShipLocalPosition();
        DestinationLocal = FVector2D(Local.X, Local.Y);
    }
}

void ACrewMember::SetRoleLabel(const FString& Label)
{
    RoleText->SetText(FText::FromString(Label));
}

void ACrewMember::SetWorkDestination(double LocalX, double LocalY)
{
    DestinationLocal = FVector2D(LocalX, LocalY);
}

FVector ACrewMember::GetShipLocalPosition() const
{
    return Ship ? Ship->GetActorTransform().InverseTransformPosition(GetActorLocation()) : FVector::ZeroVector;
}

bool ACrewMember::HasReachedDestination() const
{
    const FVector Local = GetShipLocalPosition();
    return FVector2D::Distance(FVector2D(Local.X, Local.Y), DestinationLocal) < 50.f;
}

void ACrewMember::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (!IsValid(Ship) || HasReachedDestination()) return;
    const FVector Local = GetShipLocalPosition();
    const FVector TargetLocal(DestinationLocal.X, DestinationLocal.Y, Local.Z);
    const FVector TargetWorld = Ship->GetActorTransform().TransformPosition(TargetLocal);
    const FVector Delta = TargetWorld - GetActorLocation();
    if (!Delta.IsNearlyZero()) SetActorRotation(FRotator(0.f, Delta.Rotation().Yaw, 0.f));
    SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), TargetWorld, DeltaSeconds, 150.f));
}
