//
//  game.h
//  Risk v1.0
//
//  Created by Josh Nestman on 6/13/17.
//  Copyright © 2017 Josh Nestman. All rights reserved.
//

#ifndef game_h
#define game_h

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <list>
#include "player.h"
#include "territory.h"
#include "battleSim.h"
 
class Game{
private:
    //This bit is for the sdl window
    const int WIDTH = 800, HEIGHT = 600;
    
    //territories is the master list containing all the territories and their values
    std::list<Territory> territories;
    
    //connect is used for determining which territories are connected
    std::list<std::string> connect;
    std::list<std::string>::iterator connectIt;
    
    //seed is used to seed territories with all of its values
    Territory seed;
    
    //initilizing the players
    Player *human;
    Player *bot1;
    Player *bot2;
    Player *bot3;
    Player *bot4;
    
    SDL_Surface *imageSurface = NULL;
    SDL_Surface * windowSurface = NULL;
    
    SDL_Window *window;
    SDL_Event windowEvent;
    
    SDL_Surface *message = NULL;
    TTF_Font *font = NULL;
    char text[20] = "Error";
    SDL_Color textColor = { 0, 0, 0 };
    
    //This load of garbage is for the sdl displays
    char ptInfo[24] = "# Player Territories: ";
    char ptNum[24] = "";
    char reinforceInfo[24] = "# of Reinforcements: ";
    char pReinforce[24] = "";
    char phaseText[24] = "Current Turn Phase: ";
    char phaseDisplay[24] = "";
    char click1Text[12] = "Selected = ";
    char click1Display[24] = "None";
    char click2Text[13] = "Attacking = ";
    char click2Display[24] = "None";
    char endButton[10] = "End Phase";
    char victory[10] = "You Win!";
    char loss[10] = "You Lose!";
    
    std::string currTurn;
    
    //value and postText are both used to display all of the army values across the map
    Territory value;
    SDL_Rect postText;
    
    //click1 and click2 will be used for the battle phase. click1 for selecting the player's own
    // territory and click2 for the chosen territory to engage in battle
    std::string click1;
    std::string click2;
    
    //BattleSim will fight the battles for everyone
    BattleSim battle;
    
public:
    Game() {
        territories = seed.seedTerritories();
        
        human = new Player("Human", territories);
        bot1 = new Player("bot1", territories);
        bot2 = new Player("bot2", territories);
        bot3 = new Player("bot3", territories);
        bot4 = new Player("bot4", territories);
        
        postText.x = 0;
        postText.y = 0;
        message = TTF_RenderText_Solid( font, text, textColor);
        
        currTurn = "initial";
        
        click1 = "";
        click2 = "";
    }
    
    ~Game() {
        delete human;
        delete bot1;
        delete bot2;
        delete bot3;
        delete bot4;
    }
    
    void run();
    SDL_Color ownerColor(Territory value);
    SDL_Rect getPosition(int i);
    void getClickPos(int x, int y, std::string &currTurn, std::list<Territory> &masterList,
                     std::string &click1, std::string &click2);
};


#endif /* game_h */
