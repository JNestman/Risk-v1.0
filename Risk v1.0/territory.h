//
//  territory.h
//  Risk v1.0
//
//  Created by Josh Nestman on 6/10/17.
//  Copyright © 2017 Josh Nestman. All rights reserved.
//

#ifndef territory_h
#define territory_h
#include <iostream>
#include <string>
#include <list>


class Territory {
private:
    std::string name;
    int armyValue;
    std::string owner;
    std::list<std::string> connectedTo;
    
public:
    //Getters and setters
    std::string getName() {return name;};
    void setName(std::string newName) { name = newName;};
    int getArmyValue() {return armyValue;};
    void setArmyValue(int newArmy) { armyValue = newArmy;};
    std::string getOwner() {return owner;};
    void setOwner(std::string newOwner) {owner = newOwner;};
    std::list<std::string> getConnectedTo() {return connectedTo;};
    void setConnectedTo(std::list<std::string> newConnectedTo) {connectedTo = newConnectedTo;};
    
    //This will seed the initial game with territories, army values of 1, and their owners.
    std::list<Territory> seedTerritories();
    std::string seedOwner(int h, int b1, int b2, int b3, int b4, int r);
    std::list<std::string> connectTerritories(std::string name);
    Territory findTerritory(int i, std::list<Territory> masterList);
    
    //This is for the battle phase to check that a territory is touching the player's
    // selected territory
    bool isConnectedTo(std::string selected);
};

#endif /* territory_h */
