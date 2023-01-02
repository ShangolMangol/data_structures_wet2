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
        teamsByAbility.root = teamsByAbility.deleteNode(teamsByAbility.root, teamNode->data);

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

        teamsByAbility.root = teamsByAbility.insert(teamsByAbility.root, teamNode->data);
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

    team1->rootPlayer->gamesPlayedAux += 1;
    team2->rootPlayer->gamesPlayedAux += 1;


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
	if(playerId <= 0)
        return StatusType::INVALID_INPUT;

    shared_ptr<Player> player = allPlayers.find(playerId);
    if(player == nullptr)
        return StatusType::FAILURE;

    Player* root = player->getRootUpdateRootPath();
    if(root == nullptr)
        return player->gamesPlayedAux;
    return player->gamesPlayedAux + root->gamesPlayedAux;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
    if(playerId <=0 || cards < 0)
        return StatusType::INVALID_INPUT;

    shared_ptr<Player> player = allPlayers.find(playerId);
    if(player == nullptr)
        return StatusType::FAILURE;

    Player* root = player->getRootUpdateRootPath();
    if(root == nullptr) //player is the root
    {
        if(player->teamPointer == nullptr) //is team deleted
        {
            return StatusType::FAILURE;
        }
        else
        {
            player->cards += cards;
            return StatusType::SUCCESS;
        }
    }

    if(root->teamPointer == nullptr)
    {
        return StatusType::FAILURE;
    }
    else
    {
        player->cards += cards;
        return StatusType::SUCCESS;
    }


	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
    if(playerId <=0)
        return StatusType::INVALID_INPUT;

    shared_ptr<Player> player = allPlayers.find(playerId);
    if(player == nullptr)
        return StatusType::FAILURE;

    player->getRootUpdateRootPath();
    return player->cards;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId <= 0)
        return StatusType::INVALID_INPUT;

    AVLNode<shared_ptr<Team>>* teamNode = teamsById.findNode(teamsById.root, teamId);
    if(teamNode == nullptr)
        return StatusType::FAILURE;

    return teamNode->data->points;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	if(i < 0)
        return StatusType::FAILURE;
    AVLNode<shared_ptr<Team>>* teamNode = teamsByAbility.getIthNode(i + 1);
    if(teamNode == nullptr)
        return StatusType::FAILURE;

    return teamNode->data->teamId;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
    if(playerId <= 0)
        return StatusType::INVALID_INPUT;

    shared_ptr<Player> player = allPlayers.find(playerId);
    if(player == nullptr)
        return StatusType::FAILURE;

    Player* root = player->getRootUpdateRootPath();

    if(root == nullptr)
    {
        if(player->teamPointer == nullptr)
            return StatusType::FAILURE;
        return player->spiritAux;
    }
    else
    {
        if(root->teamPointer == nullptr)
            return StatusType::FAILURE;
        return root->spiritAux * player->spiritAux;
    }
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
    //teamId1 is buyer, teamId2 is bought
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
        return StatusType::INVALID_INPUT;

    AVLNode<shared_ptr<Team>>* teamNode1 = teamsById.findNode(teamsById.root, teamId1);
    if(teamNode1 == nullptr)
        return StatusType::FAILURE;
    AVLNode<shared_ptr<Team>>* teamNode2 = teamsById.findNode(teamsById.root, teamId2);
    if(teamNode2 == nullptr)
        return StatusType::FAILURE;

    shared_ptr<Team> team1 = teamNode1->data, team2 = teamNode2->data;

    try {
        teamsById.root = teamsById.deleteNode(teamsById.root, teamId2);
        teamsByAbility.root = teamsByAbility.deleteNode(teamsByAbility.root, team1);
        teamsByAbility.root = teamsByAbility.deleteNode(teamsByAbility.root, team2);

        team1->buyTeam(team2.get());

        teamsByAbility.root = teamsByAbility.insert(teamsByAbility.root, team1);

    }
    catch (std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;


}










