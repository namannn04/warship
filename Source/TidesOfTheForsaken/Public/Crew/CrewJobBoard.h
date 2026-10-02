#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>

namespace Tides::Crew
{
enum class ERole : std::uint8_t { Sailor = 1, Gunner = 2, Carpenter = 4, Lookout = 8, Helmsman = 16 };
enum class EJobKind : std::uint8_t { ReloadCannon, PatchHull, PumpBilge, ExtinguishFire, TrimSails, WatchHorizon, Steer };

struct FJob
{
    int Id = 0;
    EJobKind Kind = EJobKind::WatchHorizon;
    int TargetId = 0;
    int Priority = 0;
    std::uint8_t EligibleRoles = 0;
    double X = 0.0;
    double Y = 0.0;
    int ClaimedBy = -1;
};

class FJobBoard
{
public:
    int Post(EJobKind Kind, int TargetId, int Priority, std::uint8_t EligibleRoles, double X, double Y)
    {
        for (FJob& Job : Jobs)
        {
            if (Job.Kind == Kind && Job.TargetId == TargetId)
            {
                Job.Priority = Priority;
                Job.EligibleRoles = EligibleRoles;
                Job.X = X;
                Job.Y = Y;
                return Job.Id;
            }
        }
        const int Id = NextId++;
        Jobs.push_back({ Id, Kind, TargetId, Priority, EligibleRoles, X, Y, -1 });
        return Id;
    }

    int ClaimBest(int CrewId, ERole Role, double X, double Y)
    {
        FJob* Best = nullptr;
        double BestScore = -1e30;
        for (FJob& Job : Jobs)
        {
            if (Job.ClaimedBy != -1 || (Job.EligibleRoles & static_cast<std::uint8_t>(Role)) == 0) continue;
            const double Distance = std::hypot(Job.X - X, Job.Y - Y);
            const double Score = Job.Priority * 10000.0 - Distance;
            if (Score > BestScore)
            {
                Best = &Job;
                BestScore = Score;
            }
        }
        if (!Best) return -1;
        Best->ClaimedBy = CrewId;
        return Best->Id;
    }

    const FJob* Find(int JobId) const
    {
        for (const FJob& Job : Jobs) if (Job.Id == JobId) return &Job;
        return nullptr;
    }

    bool Complete(int JobId, int CrewId)
    {
        auto It = std::find_if(Jobs.begin(), Jobs.end(), [=](const FJob& Job) {
            return Job.Id == JobId && Job.ClaimedBy == CrewId;
        });
        if (It == Jobs.end()) return false;
        Jobs.erase(It);
        return true;
    }

    void ReleaseCrew(int CrewId)
    {
        for (FJob& Job : Jobs) if (Job.ClaimedBy == CrewId) Job.ClaimedBy = -1;
    }

    bool Cancel(EJobKind Kind, int TargetId)
    {
        const auto It = std::find_if(Jobs.begin(), Jobs.end(), [=](const FJob& Job) {
            return Job.Kind == Kind && Job.TargetId == TargetId;
        });
        if (It == Jobs.end()) return false;
        Jobs.erase(It);
        return true;
    }

    std::size_t Count() const { return Jobs.size(); }

private:
    std::vector<FJob> Jobs;
    int NextId = 1;
};
} // namespace Tides::Crew
