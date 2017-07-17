//
//  player.cpp
//  Risk v1.0
//
//  Created by Josh Nestman on 6/11/17.
//  Copyright © 2017 Josh Nestman. All rights reserved.
//

#include "player.h"

/*********************************************************************
 * -seedPlayerTerritories: This function will seed the initial territories
 *  for each player
 *********************************************************************/
void Player::seedPlayerTerritories(std::list<Territory> masterList, std::string playerName)
{
    for (std::list<Territory>::iterator it = masterList.begin(); it != masterList.end(); it++ )
    {
        if (it->getOwner() == playerName)
            playerTerritories.push_back(*it);
    }
}

/*********************************************************************
 * -seedPlayerTerritories: This function will seed the initial territories
 *  for each player
 *********************************************************************/
void Player::botInitialArmy(std::list<Territory> &masterList, std::string playerName)
{
    std::list<Territory>::iterator it = masterList.begin();
    while (reinforcements)
    {
        if (it->getOwner() == playerName)
        {
            it->setArmyValue(it->getArmyValue() + 1);
            reinforcements--;
        }
        it++;
    }
}
/*********************************************************************
 * -Display: this is for testing the player's territory
 *********************************************************************/
void Player::display()
{
    std::list<std::string> connect;
    std::list<std::string>::iterator connectIt;
    int count = 0;
    for (std::list<Territory>::iterator it = playerTerritories.begin(); it != playerTerritories.end(); it++ )
    {
        std::cout << "Territory Name: " << it->getName() << std::endl;
        std::cout << "Territory owner: " << it->getOwner() << std::endl;
        connect = it->getConnectedTo();
        std::cout << "Connected to: ";
        for(connectIt = connect.begin(); connectIt != connect.end(); connectIt++)
        {
            std::cout << *connectIt << " ";
        }
        count++;
    }
    std::cout << "\n\nNumber of territories: " << count << " " << std::endl << std::endl;

}
