//
// Created by idota on 28/11/2022.
//

#include "Player.h"
#include "ComparePlayerById.h"

bool ComparePlayerById::isLeftSmaller(std::shared_ptr<Player> &player, int currentId)
{
    return player->playerId < currentId;
}

bool ComparePlayerById::isLeftSmaller(std::shared_ptr<Player> &player, std::shared_ptr<Player> &currentPlayer)
{
    return player->playerId < currentPlayer->playerId;
}

bool ComparePlayerById::isEqual(std::shared_ptr<Player> &player, int currentId)
{
    return player->playerId == currentId;
}

bool ComparePlayerById::isEqual(std::shared_ptr<Player> &player, std::shared_ptr<Player> &currentPlayer)
{
    return player->playerId == currentPlayer->playerId;
}

