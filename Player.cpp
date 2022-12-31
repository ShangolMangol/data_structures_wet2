//
// Created by idota on 27/12/2022.
//

#include "Player.h"
#include "Team.h"

Player::Player(int playerId, const permutation_t permutation, int i1, int i2, int i3, bool b, Player *pPlayer,
               Team *pTeam) : playerId(playerId), gamesPlayed(i1), spirit(permutation),
               ability(i2), cards(i3), isGoalkeeper(b), parent(pPlayer)
{
    if(parent == nullptr)
    {
        gamesPlayedAux = gamesPlayed;
        spiritAux = spirit;
        teamPointer = pTeam;
    }
    else
    {
        teamPointer = nullptr;
        permutation_t teamSpirit = pTeam->teamSpirit;
        spiritAux = parent->spiritAux.inv() * teamSpirit * spirit;
        gamesPlayedAux = gamesPlayed - parent->gamesPlayedAux;
    }
}

Player* Player::getRootUpdateRootPath()
{
    if(this->parent == nullptr)
        return nullptr;

    if(this->parent->parent == nullptr)
        return parent;

    Player* nextParent = this->parent;
    Player* treeRoot = nextParent;
    int gamesPlayedSum = gamesPlayedAux;
    permutation_t partialSpirit = spiritAux;
    while(nextParent != nullptr)
    {
        gamesPlayedSum += nextParent->gamesPlayedAux;
        partialSpirit = nextParent->spiritAux * partialSpirit;
        treeRoot = nextParent;
        nextParent = nextParent->parent;
    }

    Player* current = this;
    while(current != treeRoot)
    {
        nextParent = current->parent;
        current->parent = treeRoot;
        int currentGamesPlayedAux = current->gamesPlayedAux;
        permutation_t currentSpiritAux = current->spiritAux;
        current->gamesPlayedAux = gamesPlayedSum - treeRoot->gamesPlayedAux;
        current->spiritAux = treeRoot->spiritAux.inv() * partialSpirit;

        gamesPlayedSum -= currentGamesPlayedAux;
        partialSpirit = partialSpirit * currentSpiritAux.inv();

        current = nextParent;
    }

    return treeRoot;
}
