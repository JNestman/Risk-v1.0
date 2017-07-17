//
//  battleSim.cpp
//  Risk v1.0
//
//  Created by Josh Nestman on 7/17/17.
//  Copyright © 2017 Josh Nestman. All rights reserved.
//

#include "battleSim.h"
int BattleSim::findHighest(int aR1, int aR2, int aR3)
{
    if (aR1 >= aR2 && aR1 >= aR3)
        return aR1;
    else if (aR2 >= aR1 && aR2 >= aR3)
        return aR2;
    else
        return aR3;
}

int BattleSim::findSecond(int aR1, int aR2, int aR3, int high)
{
    int low = 0;
    
    if (aR1 < aR2 && aR1 < aR3)
        low = aR1;
    else if (aR2 < aR1 && aR2 < aR3)
        low = aR2;
    else
        low = aR3;
    
    if (aR1 != high && aR1 != low)
        return aR1;
    else if (aR2 != high && aR2 != low)
        return aR2;
    else
        return aR3;
    
}

void BattleSim::fightBattle(std::list<Territory> &masterList, std::string click1, std::string click2)
{
    std::list<Territory>::iterator attackArmy;
    std::list<Territory>::iterator defenceArmy;
    for (attackArmy = masterList.begin(); attackArmy != masterList.end(); attackArmy++)
    {
        if (attackArmy->getName() == click1)
            break;
        
    }
    for (defenceArmy = masterList.begin(); defenceArmy != masterList.end(); defenceArmy++)
    {
        if (defenceArmy->getName() == click2)
            break;
        
    }
    while (attackArmy->getArmyValue() > 1 && defenceArmy->getArmyValue() > 0)
    {
        int aR1 = 0;
        int aR2 = 0;
        
        int aR3 = 0;
        int dR1 = 0;
        int dR2 = 0;
        int aH = 0;
        int aM = 0;
        int temp = 0;
        
        aR1 = (rand() % 6 + 1);
        aR2 = (rand() % 6 + 1);
        aR3 = (rand() % 6 + 1);
        dR1 = (rand() % 6 + 1);
        dR2 = (rand() % 6 + 1);
        
        aH = findHighest(aR1, aR2, aR3);
        aM = findSecond(aR1, aR2, aR3, aH);
        
        if (dR1 < dR2)
        {
            temp = dR1;
            dR1 = dR2;
            dR2 = temp;
        }
        
        if (attackArmy->getArmyValue() > 3)
        {
            if (defenceArmy->getArmyValue() >= 2)
            {
                if (aH > dR1)
                    defenceArmy->setArmyValue(defenceArmy->getArmyValue() - 1);
                else
                    attackArmy->setArmyValue(attackArmy->getArmyValue() - 1);
                if (aM > dR2)
                    defenceArmy->setArmyValue(defenceArmy->getArmyValue() - 1);
                else
                    attackArmy->setArmyValue(attackArmy->getArmyValue() - 1);
            }
            else
            {
                dR1 =(rand() % 6 + 1);
                if (aH > dR1)
                    defenceArmy->setArmyValue(defenceArmy->getArmyValue() - 1);
                else
                    attackArmy->setArmyValue(attackArmy->getArmyValue() - 1);
            }
        }
        else if (attackArmy->getArmyValue() == 3)
        {
            aH = (rand() % 6 + 1);
            aM = (rand() % 6 + 1);
            if (aH < aM)
            {
                temp = aH;
                aH = aM;
                aM = temp;
            }
            
            if (defenceArmy->getArmyValue() >= 2)
            {
                if (aH > dR1)
                    defenceArmy->setArmyValue(defenceArmy->getArmyValue() - 1);
                else
                    defenceArmy->setArmyValue(defenceArmy->getArmyValue() - 1);
                if (aM > dR2)
                    defenceArmy->setArmyValue(defenceArmy->getArmyValue() - 1);
                else
                    attackArmy->setArmyValue(attackArmy->getArmyValue() - 1);
            }
            else
            {
                dR1 =(rand() % 6 + 1);
                if (aH > dR1)
                    defenceArmy->setArmyValue(defenceArmy->getArmyValue() - 1);
                else
                    attackArmy->setArmyValue(attackArmy->getArmyValue() - 1);
            }
        }
        else if (attackArmy->getArmyValue() == 2)
        {
            aH =(rand() % 6 + 1);
            
            if (defenceArmy->getArmyValue() >= 2)
            {
                if (aH > dR1)
                    defenceArmy->setArmyValue(defenceArmy->getArmyValue() - 1);
                else
                    attackArmy->setArmyValue(attackArmy->getArmyValue() - 1);
            }
            else
            {
                dR1 =(rand() % 6 + 1);
                if (aH > dR1)
                    defenceArmy->setArmyValue(defenceArmy->getArmyValue() - 1);
                else
                    attackArmy->setArmyValue(attackArmy->getArmyValue() - 1);
            }
        }
    }
    
    if (defenceArmy->getArmyValue() <= 0)
    {
        defenceArmy->setOwner(attackArmy->getOwner());
        defenceArmy->setArmyValue(attackArmy->getArmyValue() - 1);
        attackArmy->setArmyValue(1);
    }
}