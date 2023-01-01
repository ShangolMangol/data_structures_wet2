//
// Created by idota on 26/12/2022.
//

#include "Team.h"
#include "Player.h"

Team::Team(int teamId) : teamId(teamId), points(0),
totalPlayers(0), totalAbility(0), teamSpirit(permutation_t::neutral()), isValid(false), rootPlayer(nullptr)
{}

void Team::buyTeam(Team *boughtTeam)
{
    int oldTotalPlayers = this->totalPlayers;
    permutation_t oldTeamSpirit = this->teamSpirit;
    this->points += boughtTeam->points;
    this->totalPlayers += boughtTeam->totalPlayers;
    this->totalAbility += boughtTeam->totalAbility;
    this->teamSpirit = this->teamSpirit * boughtTeam->teamSpirit;
    this->isValid = this->isValid || boughtTeam->isValid;

    if(boughtTeam->rootPlayer == nullptr)
        return;

    if(this->rootPlayer == nullptr)
    {
        boughtTeam->rootPlayer->teamPointer = this;
        this->rootPlayer = boughtTeam->rootPlayer;
        return;
    }

    //start unite union-find process
    if(oldTotalPlayers >= boughtTeam->totalPlayers)
    {
        boughtTeam->rootPlayer->spiritAux = this->rootPlayer->spiritAux.inv() * oldTeamSpirit * boughtTeam->rootPlayer->spiritAux;
        boughtTeam->rootPlayer->gamesPlayedAux = boughtTeam->rootPlayer->gamesPlayedAux - this->rootPlayer->gamesPlayedAux;
        boughtTeam->rootPlayer->parent = this->rootPlayer;
        boughtTeam->rootPlayer->teamPointer = nullptr;
    }
    else
    {
        boughtTeam->rootPlayer->spiritAux = oldTeamSpirit * boughtTeam->rootPlayer->spiritAux;
        this->rootPlayer->spiritAux = boughtTeam->rootPlayer->spiritAux.inv() * this->rootPlayer->spiritAux;
        this->rootPlayer->gamesPlayedAux = this->rootPlayer->gamesPlayedAux - boughtTeam->rootPlayer->gamesPlayedAux;
        this->rootPlayer->parent = boughtTeam->rootPlayer;
        this->rootPlayer->teamPointer = nullptr;
        boughtTeam->rootPlayer->teamPointer = this;
        this->rootPlayer = boughtTeam->rootPlayer;
    }
}
