//
//  territory.cpp
//  Risk v1.0
//
//  Created by Josh Nestman on 6/10/17.
//  Copyright © 2017 Josh Nestman. All rights reserved.
//

#include "territory.h"
#include <algorithm>

/*********************************************************************
 * -connectTerritories will make a new list of all the territories a 
 *  specified territory is connected to.
 *********************************************************************/

std::list<std::string> Territory::connectTerritories(std::string name) {
    std::list<std::string> ctList = {""};
    
    if (name == "Alaska")
    {
        ctList.push_back("Kamchatka");
        ctList.push_back("Northwest Territory");
        ctList.push_back("Alberta");
    }
    else if (name == "Northwest Territory")
    {
        ctList.push_back("Alaska");
        ctList.push_back("Greenland");
        ctList.push_back("Alberta");
        ctList.push_back("Ontario");
    }
    else if (name == "Greenland")
    {
        ctList.push_back("Northwest Territory");
        ctList.push_back("Ontario");
        ctList.push_back("Eastern Canada");
        ctList.push_back("Iceland");
    }
    else if (name == "Alberta")
    {
        ctList.push_back("Alaska");
        ctList.push_back("Northwest Territory");
        ctList.push_back("Ontario");
        ctList.push_back("Western United States");
    }
    else if (name == "Ontario")
    {
        ctList.push_back("Alberta");
        ctList.push_back("Northwest Territory");
        ctList.push_back("Greenland");
        ctList.push_back("Eastern Canada");
        ctList.push_back("Western United States");
        ctList.push_back("Eastern United States");
    }
    else if (name == "Eastern Canada")
    {
        ctList.push_back("Ontario");
        ctList.push_back("Greenland");
        ctList.push_back("Eastern United States");
    }
    else if (name == "Western United States")
    {
        ctList.push_back("Alberta");
        ctList.push_back("Ontario");
        ctList.push_back("Eastern United States");
        ctList.push_back("Central America");
    }
    else if (name == "Eastern United States")
    {
        ctList.push_back("Western United States");
        ctList.push_back("Ontario");
        ctList.push_back("Eastern Canada");
        ctList.push_back("Central America");
    }
    else if (name == "Central America")
    {
        ctList.push_back("Venezuala");
        ctList.push_back("Western United States");
        ctList.push_back("Eastern United States");
    }
    else if (name == "Venezuala")
    {
        ctList.push_back("Central America");
        ctList.push_back("Peru");
        ctList.push_back("Brazil");
    }
    else if (name == "Peru")
    {
        ctList.push_back("Venezuala");
        ctList.push_back("Brazil");
        ctList.push_back("Argentina");
    }
    else if (name == "Argentina")
    {
        ctList.push_back("Brazil");
        ctList.push_back("Peru");
    }
    else if (name == "Brazil")
    {
        ctList.push_back("Venezuala");
        ctList.push_back("Peru");
        ctList.push_back("Argentina");
        ctList.push_back("North Africa");
    }
    else if (name == "North Africa")
    {
        ctList.push_back("Brazil");
        ctList.push_back("Western Europe");
        ctList.push_back("Eastern Europe");
        ctList.push_back("Egypt");
        ctList.push_back("East Africa");
        ctList.push_back("Central Africa");
    }
    else if (name == "Central Africa")
    {
        ctList.push_back("North Africa");
        ctList.push_back("East Africa");
        ctList.push_back("South Africa");
    }
    else if (name == "South Africa")
    {
        ctList.push_back("Central Africa");
        ctList.push_back("East Africa");
        ctList.push_back("Madagascar");
    }
    else if (name == "Madagascar")
    {
        ctList.push_back("South Africa");
        ctList.push_back("East Africa");
    }
    else if (name == "East Africa")
    {
        ctList.push_back("Madagascar");
        ctList.push_back("South Africa");
        ctList.push_back("Central Africa");
        ctList.push_back("North Africa");
        ctList.push_back("Egypt");
        ctList.push_back("Middle East");
    }
    else if (name == "Egypt")
    {
        ctList.push_back("East Africa");
        ctList.push_back("North Africa");
        ctList.push_back("Southern Europe");
        ctList.push_back("Middle East");
    }
    else if (name == "Western Europe")
    {
        ctList.push_back("North Africa");
        ctList.push_back("Great Britian");
        ctList.push_back("Northern Europe");
        ctList.push_back("Southern Europe");
    }
    else if (name == "Great Britian")
    {
        ctList.push_back("Western Europe");
        ctList.push_back("Iceland");
        ctList.push_back("Scandinavia");
        ctList.push_back("Northern Europe");
    }
    else if (name == "Iceland")
    {
        ctList.push_back("Greenland");
        ctList.push_back("Great Britian");
        ctList.push_back("Scandinavia");
    }
    else if (name == "Northern Europe")
    {
        ctList.push_back("Great Britian");
        ctList.push_back("Scandinavia");
        ctList.push_back("Western Europe");
        ctList.push_back("Southern Europe");
        ctList.push_back("Russia");
    }
    else if (name == "Southern Europe")
    {
        ctList.push_back("Western Europe");
        ctList.push_back("Northern Europe");
        ctList.push_back("Russia");
        ctList.push_back("North Africa");
        ctList.push_back("Egypt");
        ctList.push_back("Middle East");
    }
    else if (name == "Scandinavia")
    {
        ctList.push_back("Great Britian");
        ctList.push_back("Iceland");
        ctList.push_back("Northern Europe");
        ctList.push_back("Russia");
    }
    else if (name == "Russia")
    {
        ctList.push_back("Scandinavia");
        ctList.push_back("Northern Europe");
        ctList.push_back("Southern Europe");
        ctList.push_back("Middle East");
        ctList.push_back("Afghanistan");
        ctList.push_back("Ural");
    }
    else if (name == "Middle East")
    {
        ctList.push_back("Russia");
        ctList.push_back("Southern Europe");
        ctList.push_back("Egypt");
        ctList.push_back("East Africa");
        ctList.push_back("Afghanistan");
        ctList.push_back("India");
    }
    else if (name == "Afghanistan")
    {
        ctList.push_back("Russia");
        ctList.push_back("Middle East");
        ctList.push_back("India");
        ctList.push_back("China");
        ctList.push_back("Ural");
    }
    else if (name == "Ural")
    {
        ctList.push_back("Russia");
        ctList.push_back("Afghanistan");
        ctList.push_back("China");
        ctList.push_back("Siberia");
    }
    else if (name == "Siberia")
    {
        ctList.push_back("Ural");
        ctList.push_back("China");
        ctList.push_back("Mongolia");
        ctList.push_back("Irkutsk");
        ctList.push_back("Yakutsk");
    }
    else if (name == "Yakutsk")
    {
        ctList.push_back("Siberia");
        ctList.push_back("Irkutsk");
        ctList.push_back("Kamchatka");
    }
    else if (name == "Kamchatka")
    {
        ctList.push_back("Yatkutsk");
        ctList.push_back("Alaska");
        ctList.push_back("Irkutsk");
        ctList.push_back("Mongolia");
        ctList.push_back("Japan");
    }
    else if (name == "Irkutsk")
    {
        ctList.push_back("Siberia");
        ctList.push_back("Yakutsk");
        ctList.push_back("Kamchatka");
        ctList.push_back("Mongolia");
    }
    else if (name == "Mongolia")
    {
        ctList.push_back("Siberia");
        ctList.push_back("Irkutsk");
        ctList.push_back("Kamchatka");
        ctList.push_back("Japan");
        ctList.push_back("China");
    }
    else if (name == "Japan")
    {
        ctList.push_back("Kamchatka");
        ctList.push_back("Mongolia");
    }
    else if (name == "China")
    {
        ctList.push_back("Mongolia");
        ctList.push_back("Southeast Asia");
        ctList.push_back("India");
        ctList.push_back("Afghanistan");
        ctList.push_back("Ural");
        ctList.push_back("Siberia");
    }
    else if (name == "India")
    {
        ctList.push_back("China");
        ctList.push_back("Southeast Asia");
        ctList.push_back("Middle East");
        ctList.push_back("Afghanistan");
    }
    else if (name == "Southeast Asia")
    {
        ctList.push_back("China");
        ctList.push_back("India");
        ctList.push_back("Indonesia");
    }
    else if (name == "Indonesia")
    {
        ctList.push_back("Southeast Asia");
        ctList.push_back("New Guinea");
        ctList.push_back("Western Australia");
    }
    else if (name == "New Guinea")
    {
        ctList.push_back("Indonesia");
        ctList.push_back("Western Australia");
        ctList.push_back("Eastern Australia");
    }
    else if (name == "Western Australia")
    {
        ctList.push_back("Indonesia");
        ctList.push_back("Eastern Australia");
        ctList.push_back("New Guinea");
    }
    else if (name == "Eastern Australia")
    {
        ctList.push_back("New Guinea");
        ctList.push_back("Western Australia");
    }
    
    return ctList;
}

/*********************************************************************
 * -seedOwner will randomize the initial owner of each territory so as
 *  each game will become unique.
 *********************************************************************/
std::string Territory::seedOwner(int h, int b1, int b2, int b3, int b4, int r) {
    if (r == 0)
    {
        h += 1;
        return "Human";
    }
    else if (r == 1)
    {
        b1 += 1;
        return "bot1";
    }
    else if (r == 2)
    {
        b2 += 1;
        return "bot2";
    }
    else if (r == 3)
    {
        b3 += 1;
        return "bot3";
    }
    else
    {
        b4 += 1;
        return "bot4";
    }
}

/*********************************************************************
 * -seedTerritories will do the initial seeding at the begining of the game
 *  it will take care of creating the master list of territories and their data
 *********************************************************************/
std::list<Territory> Territory::seedTerritories() {
    std::list<Territory> initialSeed;
    Territory insertTerritory;
    srand (time(NULL));
    int r = rand() % 5;
    int human, bot1, bot2, bot3, bot4;
    human = bot1 = bot2 = bot3 = bot4 = 0;
    insertTerritory.setName("Alaska");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Alaska"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Northwest Territory");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Northwest Territory"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Greenland");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Greenland"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Alberta");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Alberta"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Ontario");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Ontario"));
    initialSeed.push_back(insertTerritory);
    
    r = rand() % 5;
    
    insertTerritory.setName("Eastern Canada");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Eastern Canada"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Western United States");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Western United States"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Eastern United States");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Eastern United States"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Central America");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Central America"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Venezuala");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Venezuala"));
    initialSeed.push_back(insertTerritory);
 
    r = rand() % 5;
    
    insertTerritory.setName("Peru");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Peru"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Argentina");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Argentina"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Brazil");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Brazil"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("North Africa");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("North Africa"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Central Africa");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Central Africa"));
    initialSeed.push_back(insertTerritory);
    
    r = rand() % 5;
    
    insertTerritory.setName("South Africa");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("South Africa"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Madagascar");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Madagascar"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("East Africa");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("East Africa"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Egypt");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Egypt"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Western Europe");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Western Europe"));
    initialSeed.push_back(insertTerritory);
    
    r = rand() % 5;

    insertTerritory.setName("Great Britian");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Great Britian"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Iceland");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Iceland"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Scandinavia");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Scandinavia"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Northern Europe");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Northern Europe"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Southern Europe");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Southern Europe"));
    initialSeed.push_back(insertTerritory);
    
    r = rand() % 5;

    insertTerritory.setName("Russia");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Russia"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Middle East");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Middle East"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Afghanistan");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Afghanistan"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Ural");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Ural"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Siberia");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Siberia"));
    initialSeed.push_back(insertTerritory);
    
    r = rand() % 5;

    insertTerritory.setName("Yakutsk");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Yakutsk"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Kamchatka");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Kamchatka"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Irkutsk");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Irkutsk"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Mongolia");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Mongolia"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Japan");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Japan"));
    initialSeed.push_back(insertTerritory);
    
    r = rand() % 5;

    insertTerritory.setName("China");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("China"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("India");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("India"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Southeast Asia");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Southeast Asia"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Indonesia");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Indonesia"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("New Guinea");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("New Guinea"));
    initialSeed.push_back(insertTerritory);
    
    r = rand() % 5;
    
    insertTerritory.setName("Western Australia");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Western Australia"));
    initialSeed.push_back(insertTerritory);
    r++;
    if (r == 5)
        r = 0;
    insertTerritory.setName("Eastern Australia");
    insertTerritory.setOwner(seedOwner(human, bot1, bot2, bot3, bot4, r));
    insertTerritory.setArmyValue(1);
    insertTerritory.setConnectedTo(connectTerritories("Eastern Australia"));
    initialSeed.push_back(insertTerritory);

    return initialSeed;
}

/*********************************************************************
 * -findTerritory will find a specific territory from the master list and
 *  return it. This function is specifically for getting Army values
 *  on the board
 *********************************************************************/
Territory Territory::findTerritory(int i, std::list<Territory> masterList){
    Territory found;
    std::string name;
    
    
    if (i == 0)
        name = "Alaska";
    else if (i == 1)
        name = "Northwest Territory";
    else if (i == 2)
        name = "Greenland";
    else if (i == 3)
        name = "Alberta";
    else if (i == 4)
        name = "Ontario";
    else if (i == 5)
        name = "Eastern Canada";
    else if (i == 6)
        name = "Western United States";
    else if (i == 7)
        name = "Eastern United States";
    else if (i == 8)
        name = "Central America";
    else if (i == 9)
        name = "Venezuala";
    else if (i == 10)
        name = "Peru";
    else if (i == 11)
        name = "Argentina";
    else if (i == 12)
        name = "Brazil";
    else if (i == 13)
        name = "North Africa";
    else if (i == 14)
        name = "Central Africa";
    else if (i == 15)
        name = "South Africa";
    else if (i == 16)
        name = "Madagascar";
    else if (i == 17)
        name = "East Africa";
    else if (i == 18)
        name = "Egypt";
    else if (i == 19)
        name = "Western Europe";
    else if (i == 20)
        name = "Great Britian";
    else if (i == 21)
        name = "Iceland";
    else if (i == 22)
        name = "Northern Europe";
    else if (i == 23)
        name = "Southern Europe";
    else if (i == 24)
        name = "Scandinavia";
    else if (i == 25)
        name = "Russia";
    else if (i == 26)
        name = "Middle East";
    else if (i == 27)
        name = "Afghanistan";
    else if (i == 28)
        name = "Ural";
    else if (i == 29)
        name = "Siberia";
    else if (i == 30)
        name = "Yakutsk";
    else if (i == 31)
        name = "Kamchatka";
    else if (i == 32)
        name = "Irkutsk";
    else if (i == 33)
        name = "Mongolia";
    else if (i == 34)
        name = "Japan";
    else if (i == 35)
        name = "China";
    else if (i == 36)
        name = "India";
    else if (i == 37)
        name = "Southeast Asia";
    else if (i == 38)
        name = "Indonesia";
    else if (i == 39)
        name = "New Guinea";
    else if (i == 40)
        name = "Western Australia";
    else if (i == 41)
        name = "Eastern Australia";
    else
        name = "Error";
    
    for (std::list<Territory>::iterator it = masterList.begin(); it != masterList.end(); it++ )
    {
        if (it->getName() == name)
            found = *it;
    }
    
    return found;
}

/*********************************************************************
 * -isConnectedTo will check if the selected territory is connected to the
 *  current territory
 *********************************************************************/
bool Territory::isConnectedTo(std::string selected)
{
    for (std::list<std::string>::iterator it = connectedTo.begin(); it != connectedTo.end(); it++)
    {
        if (*it == selected)
            return true;
    }
        return false;
}

