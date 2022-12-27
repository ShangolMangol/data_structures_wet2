//
// Created by idota on 27/12/2022.
//

#ifndef WET2_PLAYER_H
#define WET2_PLAYER_H

#include "wet2util.h"

class Team;

class Player
{
public:
    int playerId;
    int gamesPlayed;
    permutation_t spirit;
    int ability;
    int cards;
    bool isGoalkeeper;
    Player* parent;
    int gamesPlayedAux;
    permutation_t spiritAux;
    Team* teamPointer;

    Player(int playerId, const permutation_t permutation, int i1, int i2, int i3, bool b, Player *pPlayer,
           Team* pTeam);

    Player* getRootUpdateRootPath();
};


#endif //WET2_PLAYER_H
