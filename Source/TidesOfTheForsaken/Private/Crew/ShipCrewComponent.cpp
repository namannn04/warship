#include "Crew/ShipCrewComponent.h"
#include "Combat/ShipCannon.h"
#include "Ship/ShipDamageComponent.h"
#include "GameFramework/Actor.h"

UShipCrewComponent::UShipCrewComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.TickInterval = 0.5f;
}

void UShipCrewComponent::BeginPlay()
{
    Super::BeginPlay();
    Workers.Add({ 1, Tides::Crew::ERole::Gunner, -1, 0.f, -400.0, -200.0 });
    Workers.Add({ 2, Tides::Crew::ERole::Gunner, -1, 0.f, 400.0, 200.0 });
    Workers.Add({ 3, Tides::Crew::ERole::Carpenter, -1, 0.f, -900.0, 0.0 });
}

void UShipCrewComponent::RegisterCannon(AShipCannon* Cannon)
{
    if (IsValid(Cannon)) Cannons.AddUnique(Cannon);
}

void UShipCrewComponent::UpdateJobs()
{
    UShipDamageComponent* Damage = GetOwner()->FindComponentByClass<UShipDamageComponent>();
    if (Damage && (Damage->GetBreachSeverity() > 0.f || Damage->GetHullIntegrity() < 100.f))
    {
        JobBoard.Post(Tides::Crew::EJobKind::PatchHull, 0, 100,
            static_cast<std::uint8_t>(Tides::Crew::ERole::Carpenter), -900.0, 0.0);
    }
    else JobBoard.Cancel(Tides::Crew::EJobKind::PatchHull, 0);

    if (Damage && Damage->GetWaterLevel() > 5.f)
    {
        JobBoard.Post(Tides::Crew::EJobKind::PumpBilge, 0, 80,
            static_cast<std::uint8_t>(Tides::Crew::ERole::Carpenter), -900.0, 0.0);
    }
    else JobBoard.Cancel(Tides::Crew::EJobKind::PumpBilge, 0);

    for (int32 Index = 0; Index < Cannons.Num(); ++Index)
    {
        const int TargetId = Index + 1;
        AShipCannon* Cannon = Cannons[Index];
        if (IsValid(Cannon) && Cannon->NeedsLoading() && !Cannon->IsOperated())
        {
            const FVector Local = GetOwner()->GetActorTransform().InverseTransformPosition(Cannon->GetActorLocation());
            JobBoard.Post(Tides::Crew::EJobKind::ReloadCannon, TargetId, 40,
                static_cast<std::uint8_t>(Tides::Crew::ERole::Gunner), Local.X, Local.Y);
        }
        else JobBoard.Cancel(Tides::Crew::EJobKind::ReloadCannon, TargetId);
    }
}

void UShipCrewComponent::WorkOneStep(FCrewWorker& Worker, const Tides::Crew::FJob& Job)
{
    UShipDamageComponent* Damage = GetOwner()->FindComponentByClass<UShipDamageComponent>();
    switch (Job.Kind)
    {
    case Tides::Crew::EJobKind::ReloadCannon:
        if (Cannons.IsValidIndex(Job.TargetId - 1) && IsValid(Cannons[Job.TargetId - 1]))
        {
            AShipCannon* Cannon = Cannons[Job.TargetId - 1];
            Cannon->AdvanceLoading();
            if (!Cannon->NeedsLoading()) JobBoard.Complete(Job.Id, Worker.Id);
        }
        break;
    case Tides::Crew::EJobKind::PatchHull:
        if (Damage)
        {
            Damage->RepairHull(10.f);
            if (Damage->GetBreachSeverity() <= 0.f && Damage->GetHullIntegrity() >= 100.f) JobBoard.Complete(Job.Id, Worker.Id);
        }
        break;
    case Tides::Crew::EJobKind::PumpBilge:
        if (Damage)
        {
            Damage->PumpWater(10.f);
            if (Damage->GetWaterLevel() <= 5.f) JobBoard.Complete(Job.Id, Worker.Id);
        }
        break;
    default: break;
    }
}

void UShipCrewComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (!bWorkEnabled) return;
    TimeAccumulator += DeltaTime;
    if (TimeAccumulator < 0.5f) return;
    const float Step = TimeAccumulator;
    TimeAccumulator = 0.f;
    UpdateJobs();
    for (FCrewWorker& Worker : Workers)
    {
        if (!JobBoard.Find(Worker.JobId))
        {
            Worker.JobId = JobBoard.ClaimBest(Worker.Id, Worker.Role, Worker.X, Worker.Y);
            Worker.WorkElapsed = 0.f;
        }
        const Tides::Crew::FJob* Job = JobBoard.Find(Worker.JobId);
        if (!Job) continue;
        Worker.WorkElapsed += Step;
        if (Worker.WorkElapsed < 2.f) continue;
        Worker.WorkElapsed = 0.f;
        const Tides::Crew::FJob Snapshot = *Job;
        WorkOneStep(Worker, Snapshot);
    }
}
