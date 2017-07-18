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
void Player::setNumTerritories(std::list<Territory> masterList, std::string playerName)
{
    numTerritories = 0;
    for (std::list<Territory>::iterator it = masterList.begin(); it != masterList.end(); it++ )
    {
        if (it->getOwner() == playerName)
            numTerritories++;
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

