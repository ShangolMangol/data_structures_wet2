#include "worldcup23a2.h"

using std::shared_ptr;

world_cup_t::world_cup_t() : teamsById(), teamsByAbility(), allPlayers(), totalPlayers(0)
{

}

world_cup_t::~world_cup_t()
{

}

StatusType world_cup_t::add_team(int teamId)
{
    if(teamId <= 0)
        return StatusType::INVALID_INPUT;
    AVLNode<shared_ptr<Team>>* team = teamsById.findNode(teamsById.root, teamId);
    if(team != nullptr)
        return StatusType::FAILURE;

    try
    {
        shared_ptr<Team> newTeam = shared_ptr<Team>(new Team(teamId));
        teamsById.root = teamsById.insert(teamsById.root,newTeam);
        teamsByAbility.root = teamsByAbility.insert(teamsByAbility.root,newTeam);
    } catch(std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if(teamId <= 0)
        return StatusType::INVALID_INPUT;
    AVLNode<shared_ptr<Team>>* teamNode = teamsById.findNode(teamsById.root, teamId);
    if(teamNode == nullptr)
        return StatusType::FAILURE;

    if(teamNode->data->rootPlayer != nullptr)
        teamNode->data->rootPlayer->teamPointer = nullptr;

    try {
        teamsByAbility.root = teamsByAbility.deleteNode(teamsByAbility.root, teamNode->data);
        teamsById.root = teamsById.deleteNode(teamsById.root, teamId);
    } catch (std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

	return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
	if(playerId <= 0 || teamId <= 0 || !spirit.isvalid() || gamesPlayed < 0 || cards < 0)
        return StatusType::INVALID_INPUT;

    AVLNode<shared_ptr<Team>>* teamNode = teamsById.findNode(teamsById.root, teamId);
    if(teamNode == nullptr)
        return StatusType::FAILURE;

    shared_ptr<Player> player = allPlayers.find(playerId);
    if(player != nullptr)
        return StatusType::FAILURE;

    try {
        shared_ptr<Player> newPlayer = shared_ptr<Player>(new Player(playerId, spirit,
                                                                     gamesPlayed, ability, cards,
                                                                     goalKeeper, teamNode->data->rootPlayer,
                                                                     teamNode->data.get()));
        allPlayers.insert(newPlayer);
        Team *team = teamNode->data.get();
        team->teamSpirit = team->teamSpirit * spirit;
        team->totalAbility = team->totalAbility + ability;
        team->totalPlayers = team->totalPlayers + 1;
        if(team->rootPlayer == nullptr)
            team->rootPlayer = newPlayer.get();

        if (goalKeeper)
            teamNode->data->isValid = true;
    }
    catch(std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
        return StatusType::INVALID_INPUT;

    AVLNode<shared_ptr<Team>>* teamNode1 = teamsById.findNode(teamsById.root, teamId1);
    if(teamNode1 == nullptr)
        return StatusType::FAILURE;
    AVLNode<shared_ptr<Team>>* teamNode2 = teamsById.findNode(teamsById.root, teamId2);
    if(teamNode2 == nullptr)
        return StatusType::FAILURE;

    Team *team1 = teamNode1->data.get(), *team2 = teamNode2->data.get();
    if(!team1->isValid || !team2->isValid)
        return StatusType::FAILURE;

    int score1 = team1->points + team1->totalAbility, score2 = team2->points + team2->totalAbility;

    if(score1 < score2)
    {
        team2->points += 3;
        return 3;
    }
    else if(score1 > score2)
    {
        team1->points += 3;
        return 1;
    }
    else
    {
        int spiritStrength1 = team1->teamSpirit.strength(), spiritStrength2 = team2->teamSpirit.strength();
        if(spiritStrength1 < spiritStrength2)
        {
            team2->points += 3;
            return 4;
        }
        else if(spiritStrength1 > spiritStrength2)
        {
            team1->points += 3;
            return 2;
        }
        else
        {
            team1->points += 1;
            team2->points += 1;
            return 0;
        }
    }


	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// TODO: Your code goes here
	return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
