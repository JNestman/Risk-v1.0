//
//  player.cpp
//  Risk v1.0
//
//  Created by Josh Nestman on 6/11/17.
//  Copyright © 2017 Josh Nestman. All rights reserved.
//

#include "player.h"
#include "battleSim.h"

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

/*********************************************************************
 * -handleBotTurn will.... handle the bot's turn... shocking
 *********************************************************************/
void Player::handleBotTurn(std::list<Territory> &masterList)
{
    std::list<Territory>::iterator it;
    std::list<Territory>::iterator defTerritory;
    std::list<std::string> connectedList;
    BattleSim botBattle;

    for (it = masterList.begin(); it != masterList.end(); it++)
    {
        if (it->getOwner() == playerType)
        {
            connectedList = it->getConnectedTo();
            it->setArmyValue(it->getArmyValue() + reinforceTerritory(masterList, connectedList));
            
            if (it->getArmyValue() >= 8 && !checkInactive(masterList, connectedList))
            {
                bool first = true;
                
                for (std::list<std::string>::iterator cl = connectedList.begin(); cl != connectedList.end(); cl++)
                {
                    for (std::list<Territory>::iterator it2 = masterList.begin(); it2 != masterList.end(); it2++)
                    {
                        if (*cl == it2->getName())
                        {
                            if (it2->getOwner() != playerType && first)
                            {
                                defTerritory = it2;
                                first = false;
                            }
                            else if (it2->getOwner() != playerType && defTerritory->getArmyValue() < it2->getArmyValue())
                            {
                                defTerritory = it2;
                            }
                        }
                    }
                }
                //defTerritory = getDefTerr(masterList, connectedList);
                botBattle.fightBotBattle(masterList, it->getName(), defTerritory->getName());
            }
        }
    }
}

/*********************************************************************
 * -reinforceTerritory returns the number of reinforcements that each
 *  bot's territory will recieve.
 *********************************************************************/
int Player::reinforceTerritory(std::list<Territory> masterList, std::list<std::string> connectedList)
{
    int numRei = 1;
    bool inactive = checkInactive(masterList, connectedList);
    
    if (inactive)
        return 0;
    
    for (std::list<std::string>::iterator cl = connectedList.begin(); cl != connectedList.end(); cl++)
    {
        for (std::list<Territory>::iterator it = masterList.begin(); it != masterList.end(); it++)
        {
            if (*cl == it->getName())
            {
                if (it->getOwner() == playerType && !inactive)
                {
                    numRei = 2;
                }
            }
        }
    }

    
    return numRei;
}

/*********************************************************************
 * -reinforceTerritory returns the number of reinforcements that each
 *  bot's territory will recieve.
 *********************************************************************/
bool Player::checkInactive(std::list<Territory> masterList, std::list<std::string> connectedList)
{
    for (std::list<std::string>::iterator cl = connectedList.begin(); cl != connectedList.end(); cl++)
    {
        for (std::list<Territory>::iterator it = masterList.begin(); it != masterList.end(); it++)
        {
            if (*cl == it->getName())
            {
                if (it->getOwner() != playerType)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

/*********************************************************************
 * -reinforceTerritory returns the number of reinforcements that each
 *  bot's territory will recieve.
 *********************************************************************/
std::list<Territory>::iterator Player::getDefTerr(std::list<Territory> masterList, std::list<std::string> connectedList)
{
    std::list<Territory>::iterator lowest;
    bool first = true;
    
    for (std::list<std::string>::iterator cl = connectedList.begin(); cl != connectedList.end(); cl++)
    {
        for (std::list<Territory>::iterator it = masterList.begin(); it != masterList.end(); it++)
        {
            if (*cl == it->getName())
            {
                if (it->getOwner() != playerType && first)
                {
                    lowest = it;
                    first = false;
                }
                else if (it->getOwner() != playerType && lowest->getArmyValue() < it->getArmyValue())
                {
                    lowest = it;
                }
            }
        }
    }
    return lowest;
}
