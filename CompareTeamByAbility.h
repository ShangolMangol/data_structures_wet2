//
// Created by idota on 27/12/2022.
//

#ifndef WET2_COMPARETEAMBYABILITY_H
#define WET2_COMPARETEAMBYABILITY_H

#include "Team.h"
#include <memory>

class CompareTeamByAbility
{
public:
//    bool isLeftSmaller(std::shared_ptr<Team>& team, int currentAbility);
    bool isLeftSmaller(std::shared_ptr<Team>& team, std::shared_ptr<Team>& currentTeam);
//    bool isEqual(std::shared_ptr<Team>& team, int currentAbility);
    bool isEqual(std::shared_ptr<Team>& team, std::shared_ptr<Team>& currentTeam);
};


#endif //WET2_COMPARETEAMBYABILITY_H
