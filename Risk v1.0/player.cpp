//
//  player.cpp
//  Risk v1.0
//
//  Created by Josh Nestman on 6/11/17.
//  Copyright © 2017 Josh Nestman. All rights reserved.
//

#include "player.h"

/*********************************************************************
 * -setNumTerritories: This function will set the number of territories
 *  for a given player
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
 * -botInitialArmy: This will set go out and set the board for the initial
 *  phase
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
 * -botInitialArmy: This will set go out and set the board for the initial
 *  phase
 *********************************************************************/
int Player::getContBonus(std::list<Territory> masterList, std::string playerName)
{
    int bonus = 0;
    bool owns = true;
    
    std::list<Territory>::iterator it = masterList.begin();
    //North America bonus
    while (it->getName() != "Venezuala")
    {
        if (it->getOwner() == playerName && owns)
            owns = true;
        else
            owns = false;
        it++;
    }
    if (owns)
        bonus += 5;
    
    owns = true;
    while (it->getName() != "North Africa")
    {
        if (it->getOwner() == playerName && owns)
            owns = true;
        else
            owns = false;
        it++;
    }
    if (owns)
        bonus += 2;
    
    owns = true;
    while (it->getName() != "Western Europe")
    {
        if (it->getOwner() == playerName && owns)
            owns = true;
        else
            owns = false;
        it++;
    }
    if (owns)
        bonus += 3;
    
    owns = true;
    while (it->getName() != "Middle East")
    {
        if (it->getOwner() == playerName && owns)
            owns = true;
        else
            owns = false;
        it++;
    }
    if (owns)
        bonus += 5;
    
    owns = true;
    while (it->getName() != "Indonesia")
    {
        if (it->getOwner() == playerName && owns)
            owns = true;
        else
            owns = false;
        it++;
    }
    if (owns)
        bonus += 7;
    
    owns = true;
    while (it != masterList.end())
    {
        if (it->getOwner() == playerName && owns)
            owns = true;
        else
            owns = false;
        it++;
    }
    if (owns)
        bonus += 2;
    
    return bonus;
}
