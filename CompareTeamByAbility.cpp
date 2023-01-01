//
// Created by idota on 27/12/2022.
//

#include "CompareTeamByAbility.h"

//bool CompareTeamByAbility::isLeftSmaller(std::shared_ptr<Team> &team, int currentAbility)
//{
//    return team->totalAbility < currentAbility;
//}

bool CompareTeamByAbility::isLeftSmaller(std::shared_ptr<Team> &team, std::shared_ptr<Team> &currentTeam)
{
    if(team->totalAbility < currentTeam->totalAbility)
    {
        return true;
    }
    if(team->totalAbility == currentTeam->totalAbility)
    {
        return team->teamId < currentTeam->teamId;
    }
    return false;
}

//bool CompareTeamByAbility::isEqual(std::shared_ptr<Team> &team, int currentAbility)
//{
//    return team->totalAbility == currentAbility;
//}

bool CompareTeamByAbility::isEqual(std::shared_ptr<Team> &team, std::shared_ptr<Team> &currentTeam)
{
    return team->teamId == currentTeam->teamId;
}
