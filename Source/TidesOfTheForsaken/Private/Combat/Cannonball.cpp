#include "Combat/Cannonball.h"
#include "Ship/ShipActor.h"
#include "Ship/ShipDamageComponent.h"
#include "Engine/Engine.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"

ACannonball::ACannonball()
{
    Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    SetRootComponent(Collision);
    Collision->InitSphereRadius(14.f);
    Collision->SetCollisionProfileName(TEXT("BlockAllDynamic"));
    Collision->SetNotifyRigidBodyCollision(true);
    Collision->OnComponentHit.AddDynamic(this, &ACannonball::OnImpact);

    Visual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
    Visual->SetupAttachment(Collision);
    Visual->SetRelativeScale3D(FVector(0.28f));
    Visual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (Sphere.Succeeded()) Visual->SetStaticMesh(Sphere.Object);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->UpdatedComponent = Collision;
    ProjectileMovement->InitialSpeed = 6000.f;
    ProjectileMovement->MaxSpeed = 6000.f;
    ProjectileMovement->ProjectileGravityScale = 1.f;
    InitialLifeSpan = 10.f;
}

void ACannonball::OnImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    if (AShipActor* Ship = Cast<AShipActor>(OtherActor))
    {
        Ship->GetShipDamage()->ApplyImpact(OtherComponent, 35.f);
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange,
                FString::Printf(TEXT("Ship hit: hull %.0f, water %.0f"),
                    Ship->GetShipDamage()->GetHullIntegrity(), Ship->GetShipDamage()->GetWaterLevel()));
        }
    }
    Destroy();
}
