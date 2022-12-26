//
// Created by idota on 28/11/2022.
//

#ifndef WET1_COMPARETEAMBYID_H
#define WET1_COMPARETEAMBYID_H


#include <memory>
class Team;

class CompareTeamById
{
public:
    bool isLeftSmaller(std::shared_ptr<Team>& team, int currentId);
    bool isLeftSmaller(std::shared_ptr<Team>& team, std::shared_ptr<Team>& currentTeam);
    bool isEqual(std::shared_ptr<Team>& team, int currentId);
    bool isEqual(std::shared_ptr<Team>& team, std::shared_ptr<Team>& currentTeam);

//    void insertToLeft(std::shared_ptr<Team>& team, std::shared_ptr<Team>& currentTeam);
//    void insertToRight(std::shared_ptr<Team>& team, std::shared_ptr<Team>& currentTeam);
//
//    void handleDelete(std::shared_ptr<Team>& teamToDelete);
};


#endif //WET1_COMPARETEAMBYID_H
