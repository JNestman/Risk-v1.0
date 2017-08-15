//
//  player.h
//  Risk v1.0
//
//  Created by Josh Nestman on 6/10/17.
//  Copyright © 2017 Josh Nestman. All rights reserved.
//

#ifndef player_h
#define player_h
#include "territory.h"

class Player {
private:
    int numTerritories;
    std::string playerType;
    int reinforcements;
    bool once;
    
public:
    Player(std::string newPlayer, std::list<Territory> masterList) {
        playerType = newPlayer;
        setNumTerritories(masterList, newPlayer);
        reinforcements = 0;
        once = true;
    }
    
    void setNumTerritories(std::list<Territory> masterList, std::string playerName);
    bool isAlive() {return numTerritories > 0;}
    long getNumTerritories() { return numTerritories;}
    void setReinforcements(int re) { reinforcements = re; once = false;}
    int getReinforcements() { return reinforcements; }
    
    //Get and set once is to make sure that the players don't get unlimited reinforcements
    bool getOnce() { return once;}
    void setOnce(bool change) { once = change; }
    
    void botInitialArmy(std::list<Territory> &masterList, std::string playerName);
    
    int getContBonus(std::list<Territory> masterList, std::string playerName);
    
    void handleBotTurn(std::list<Territory> &masterList, std::string playerName);
};

#endif /* player_h */
