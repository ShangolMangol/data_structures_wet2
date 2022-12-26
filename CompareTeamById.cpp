//
// Created by idota on 28/11/2022.
//

#include "CompareTeamById.h"
#include "Team.h"

bool CompareTeamById::isLeftSmaller(std::shared_ptr<Team> &team, int currentId)
{
    return team->teamId < currentId;
}

bool CompareTeamById::isLeftSmaller(std::shared_ptr<Team> &team, std::shared_ptr<Team> &currentTeam)
{
    return team->teamId < currentTeam->teamId;
}

bool CompareTeamById::isEqual(std::shared_ptr<Team> &team, int currentId)
{
    return team->teamId == currentId;
}

bool CompareTeamById::isEqual(std::shared_ptr<Team> &team, std::shared_ptr<Team> &currentTeam)
{
    return team->teamId == currentTeam->teamId;
}
//
//void CompareTeamById::insertToLeft(std::shared_ptr<Team> &team, std::shared_ptr<Team> &currentTeam)
//{
//}
//
//void CompareTeamById::insertToRight(std::shared_ptr<Team> &team, std::shared_ptr<Team> &currentTeam)
//{
//
//}
//
//void CompareTeamById::handleDelete(std::shared_ptr<Team> &teamToDelete)
//{
//
//}
