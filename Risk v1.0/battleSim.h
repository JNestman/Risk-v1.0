//
//  battleSim.h
//  Risk v1.0
//
//  Created by Josh Nestman on 7/17/17.
//  Copyright © 2017 Josh Nestman. All rights reserved.
//

#ifndef battleSim_h
#define battleSim_h

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <list>
#include "territory.h"

class BattleSim{
private:
    int attackArmy = 0;
    int defenceArmy = 0;
    int result = 0;
    int numBat = 0;
    float aWin = 0;
    float dWin = 0;
    
public:
    int findHighest(int aR1, int aR2, int aR3);
    
    int findSecond(int aR1, int aR2, int aR3, int high);
    
    void fightBattle(std::list<Territory> &masterList, std::string click1, std::string click2);

};

#endif /* battleSim_h */
