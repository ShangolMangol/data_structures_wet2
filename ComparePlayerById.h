

#ifndef WET1_COMPAREPLAYERBYID_H
#define WET1_COMPAREPLAYERBYID_H

#include <memory>


class Player;

class ComparePlayerById
{
public:
    bool isLeftSmaller(std::shared_ptr<Player>& player, int currentId);
    bool isLeftSmaller(std::shared_ptr<Player>& player, std::shared_ptr<Player>& currentPlayer);
    bool isEqual(std::shared_ptr<Player>& player, int currentId);
    bool isEqual(std::shared_ptr<Player>& player, std::shared_ptr<Player>& currentPlayer);

};


#endif //WET1_COMPAREPLAYERBYID_H
