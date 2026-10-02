#include "World/TidesGameMode.h"
#include "Character/CaptainCharacter.h"
#include "Ship/ShipActor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"
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

    AShipActor* Ship = World->SpawnActor<AShipActor>(AShipActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
    if (Ship)
    {
        if (APlayerController* PC = World->GetFirstPlayerController())
        {
            if (APawn* Pawn = PC->GetPawn()) Pawn->SetActorLocation(Ship->GetCaptainStartLocation());
        }
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
}
