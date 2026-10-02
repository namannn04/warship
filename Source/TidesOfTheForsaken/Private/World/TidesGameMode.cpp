#include "World/TidesGameMode.h"
#include "Character/CaptainCharacter.h"
#include "Ship/ShipActor.h"
#include "Ship/ShipMovementComponent.h"
#include "Crew/ShipCrewComponent.h"
#include "Crew/CrewMember.h"
#include "Interaction/HelmStation.h"
#include "Interaction/RepairStation.h"
#include "Combat/ShipCannon.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

ATidesGameMode::ATidesGameMode()
{
    DefaultPawnClass = ACaptainCharacter::StaticClass();
}

void ATidesGameMode::BeginPlay()
{
    Super::BeginPlay();
    UWorld* World = GetWorld();
    if (!World) return;

    PrototypeShip = World->SpawnActor<AShipActor>(AShipActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
    if (PrototypeShip)
    {
        AHelmStation* Helm = World->SpawnActor<AHelmStation>(AHelmStation::StaticClass(), PrototypeShip->GetHelmLocation(), PrototypeShip->GetActorRotation());
        if (Helm)
        {
            Helm->SetOwningShip(PrototypeShip);
            Helm->AttachToActor(PrototypeShip, FAttachmentTransformRules::KeepWorldTransform);
        }
        ARepairStation* Repair = World->SpawnActor<ARepairStation>(ARepairStation::StaticClass(),
            PrototypeShip->GetRepairStationLocation(), FRotator::ZeroRotator);
        if (Repair)
        {
            Repair->SetOwningShip(PrototypeShip);
            Repair->AttachToActor(PrototypeShip, FAttachmentTransformRules::KeepWorldTransform);
        }
        for (const float AlongShip : { -600.f, 0.f, 600.f })
        {
            for (const bool bPort : { true, false })
            {
                const FRotator Facing(0.f, bPort ? -90.f : 90.f, 0.f);
                AShipCannon* Cannon = World->SpawnActor<AShipCannon>(AShipCannon::StaticClass(),
                    PrototypeShip->GetCannonLocation(AlongShip, bPort), Facing);
                if (Cannon)
                {
                    Cannon->SetOwningShip(PrototypeShip);
                    PrototypeShip->GetShipCrew()->RegisterCannon(Cannon);
                    Cannon->AttachToActor(PrototypeShip, FAttachmentTransformRules::KeepWorldTransform);
                }
            }
        }
        struct FCrewSpawn { int32 Id; float X; float Y; const TCHAR* Label; };
        const FCrewSpawn CrewSpawns[] = {
            { 1, -400.f, -200.f, TEXT("GUNNER") },
            { 2, 400.f, 200.f, TEXT("GUNNER") },
            { 3, -900.f, 0.f, TEXT("CARPENTER") }
        };
        for (const FCrewSpawn& Spec : CrewSpawns)
        {
            ACrewMember* Member = World->SpawnActor<ACrewMember>(ACrewMember::StaticClass(),
                PrototypeShip->GetGunDeckCrewLocation(Spec.X, Spec.Y), FRotator::ZeroRotator);
            if (Member)
            {
                Member->SetRoleLabel(Spec.Label);
                Member->SetShip(PrototypeShip);
                PrototypeShip->GetShipCrew()->RegisterCrewMember(Spec.Id, Member);
            }
        }
        if (APlayerController* PC = World->GetFirstPlayerController())
        {
            PlaceCaptain(PC);
        }
    }

    // A passive broadside target makes damage and flooding observable in the slice.
    AShipActor* TargetShip = World->SpawnActor<AShipActor>(AShipActor::StaticClass(),
        FVector(0.f, -3500.f, 0.f), FRotator::ZeroRotator);
    if (TargetShip)
    {
        TargetShip->Tags.Add(TEXT("BroadsideTarget"));
        TargetShip->GetShipMovement()->SetSailPower(0.f);
        TargetShip->GetShipMovement()->SetAnchored(true);
        TargetShip->GetShipCrew()->SetWorkEnabled(false);
    }

    AStaticMeshActor* Ocean = World->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), FVector(0.f, 0.f, -20.f), FRotator::ZeroRotator);
    if (Ocean)
    {
        UStaticMesh* Cube = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"));
        if (Cube) Ocean->GetStaticMeshComponent()->SetStaticMesh(Cube);
        Ocean->GetStaticMeshComponent()->SetWorldScale3D(FVector(1000.f, 1000.f, 0.4f));
        Ocean->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        Ocean->GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
    }

    ADirectionalLight* Sun = World->SpawnActor<ADirectionalLight>(ADirectionalLight::StaticClass(),
        FVector::ZeroVector, FRotator(-45.f, -30.f, 0.f));
    if (Sun)
    {
        Sun->GetLightComponent()->SetMobility(EComponentMobility::Movable);
        Sun->GetLightComponent()->SetIntensity(6.f);
    }
}

void ATidesGameMode::RestartPlayer(AController* NewPlayer)
{
    Super::RestartPlayer(NewPlayer);
    PlaceCaptain(NewPlayer);
}

void ATidesGameMode::PlaceCaptain(AController* Controller) const
{
    if (IsValid(PrototypeShip) && IsValid(Controller) && IsValid(Controller->GetPawn()))
    {
        Controller->GetPawn()->SetActorLocation(PrototypeShip->GetCaptainStartLocation(), false, nullptr, ETeleportType::TeleportPhysics);
    }
}
