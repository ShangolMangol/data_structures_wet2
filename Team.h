//
// Created by idota on 26/12/2022.
//

#ifndef WET2_TEAM_H
#define WET2_TEAM_H

#include "wet2util.h"

class Player;

class Team
{
public:
    Team(int teamId);

    int teamId;
    int points;
    int totalPlayers;
    int totalAbility;
    permutation_t teamSpirit;
    bool isValid;
//    bool isCompeting;
    Player* rootPlayer;

    void buyTeam(Team* boughtTeam);
};


#endif //WET2_TEAM_H
