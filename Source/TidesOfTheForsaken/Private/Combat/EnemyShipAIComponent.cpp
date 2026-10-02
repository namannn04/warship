#include "Combat/EnemyShipAIComponent.h"
#include "Combat/ShipCannon.h"
#include "Ship/ShipActor.h"
#include "Ship/ShipMovementComponent.h"
#include "Ship/ShipDamageComponent.h"
#include "Crew/ShipCommandComponent.h"

UEnemyShipAIComponent::UEnemyShipAIComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.TickGroup = TG_PrePhysics;
    PrimaryComponentTick.TickInterval = 0.5f;
}

void UEnemyShipAIComponent::BeginPlay()
{
    Super::BeginPlay();
    if (AShipActor* Ship = Cast<AShipActor>(GetOwner()))
    {
        Ship->GetShipCommands()->AddTickPrerequisiteComponent(this);
    }
}

void UEnemyShipAIComponent::SetTarget(AShipActor* Ship)
{
    TargetShip = Ship;
}

void UEnemyShipAIComponent::RegisterCannon(AShipCannon* Cannon, Tides::NavalAI::ESide Side)
{
    if (!IsValid(Cannon)) return;
    FEnemyCannon Gun;
    Gun.Cannon = Cannon;
    Gun.Side = Side;
    Cannons.Add(Gun);
}

void UEnemyShipAIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    AShipActor* OwnShip = Cast<AShipActor>(GetOwner());
    if (!IsValid(OwnShip) || !IsValid(TargetShip) || OwnShip->GetShipDamage()->IsSunk() ||
        TargetShip->GetShipDamage()->IsSunk()) return;

    const FVector Own = OwnShip->GetActorLocation();
    const FVector Target = TargetShip->GetActorLocation();
    const Tides::NavalAI::FDecision Decision = Tides::NavalAI::Decide(
        Own.X, Own.Y, OwnShip->GetActorRotation().Yaw,
        Target.X, Target.Y, OwnShip->GetShipDamage()->GetHullIntegrity());

    OwnShip->GetShipMovement()->SetAnchored(false);
    OwnShip->GetShipCommands()->OrderHeading(static_cast<float>(Decision.DesiredHeadingDegrees));
    OwnShip->GetShipCommands()->OrderSailPower(static_cast<float>(Decision.SailPower));
    for (FEnemyCannon& Gun : Cannons)
    {
        AShipCannon* Cannon = Gun.Cannon.Get();
        if (!IsValid(Cannon)) continue;
        if (Cannon->NeedsLoading()) Cannon->AdvanceLoading();
        else if (Decision.bMayFire && Gun.Side == Decision.FiringSide) Cannon->Fire();
    }
}
