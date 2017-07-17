//
//  game.cpp
//  Risk v1.0
//
//  Created by Josh Nestman on 6/13/17.
//  Copyright © 2017 Josh Nestman. All rights reserved.
//

#include "game.h"

void Game::run() {
    //This is where the SDL madness begins
    //
    //
    
    //Check that SDL is working
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not initialize! SDL ERROR: " << SDL_GetError() << std::endl;
    }
    //Create the window
    window = SDL_CreateWindow("Risk v1.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    
    windowSurface = SDL_GetWindowSurface(window);
    
    //Check that the window was created
    if (NULL == window)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        
        return;
    }
    
    //Check that SDL_Image is working
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cout << "Could not initialize SDL_Image: " << IMG_GetError << std::endl;
        return;
    }
    
    //Create the window event
    //SDL_Event windowEvent;
    
    imageSurface = IMG_Load("Risk01.jpg");
    
    if (NULL == imageSurface)
    {
        std::cout << "SDL could not load image: " << SDL_GetError() << std::endl;
    }
    
    //This section is for getting text onto the screen
    TTF_Init();
    if (TTF_Init() < 0)
        std::cout << "TTF Error: " << TTF_GetError << std::endl;
    
    //Link to the font I have downloaded
    font = TTF_OpenFont("/Users/joshnestman/Desktop/sdl Test/sdl Test/arial.ttf", 12);
    if (!font)
        std::cout << "Font Error:" << std::endl;

    
    //This is the main loop. It wont end untill the screen is closed
    while ( true )
    {
        //This will set the human player's reinforcements at the start of their turn
        if (currTurn == "reinforce" && human->getOnce())
        {
            if (human->getNumTerritories() / 3 < 3)
                human->setReinforcements(3);
            else
                human->setReinforcements(human->getNumTerritories() / 3);
        }

        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_MOUSEBUTTONDOWN )
            {
                //If the left mouse button was pressed
                if( windowEvent.button.button == SDL_BUTTON_LEFT )
                {
                    //This if statement will handle click events for the battle phase
                    if (currTurn == "battle")
                    {
                        getClickPos(windowEvent.button.x, windowEvent.button.y, currTurn, territories, click1, click2);
                    }
                    
                    //Only valid if the human player has reinforcements left
                    //This will be used for the reinforcement phase as well as the initial phase
                    if (human->getReinforcements() > 0)
                    {
                        //This blocked out segment was for the initial x and y testing for click events
                        /*if (windowEvent.button.x > 650 && windowEvent.button.y > 430
                            && windowEvent.button.x < 710 && windowEvent.button.y < 480)
                        {
                            std::list<Territory>::iterator it = territories.begin();
                            it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
                            it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
                            it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
                            it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
                            it++;
                            
                            it->setArmyValue((it->getArmyValue() + 1));
                            human->setReinforcements(human->getReinforcements() - 1);
                            
                        }*/
                        //Click event handler for initial and reinforcements
                        getClickPos(windowEvent.button.x, windowEvent.button.y, currTurn, territories, click1, click2);
                        if (human->getReinforcements() == 0 && currTurn == "initial") //Set up for the bots initial phase
                        {
                            currTurn = "reinforce";
                            human->setOnce(true);
                            
                            if (bot1->getOnce())
                                bot1->setReinforcements((25 - bot1->getNumTerritories()));
                            
                            if (bot2->getOnce())
                                bot2->setReinforcements((25 - bot2->getNumTerritories()));
                            
                            if (bot3->getOnce())
                                bot3->setReinforcements((25 - bot3->getNumTerritories()));
                            
                            if (bot4->getOnce())
                                bot4->setReinforcements((25 - bot4->getNumTerritories()));
                            
                            bot1->botInitialArmy(territories, "bot1");
                            bot2->botInitialArmy(territories, "bot2");
                            bot3->botInitialArmy(territories, "bot3");
                            bot4->botInitialArmy(territories, "bot4");
                        }
                        else if (human->getReinforcements() == 0 && currTurn == "reinforce")
                        {
                            currTurn = "battle";
                        }
                    }
                }
                
            }
            if(SDL_QUIT == windowEvent.type)
            {
                break;
            }
        }
        //The surface for the map
        SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);
        
        //This section is for the player info in the top left
        postText.x = 40;
        postText.y = 15;
        textColor = { 0, 0, 255 };
        message = TTF_RenderText_Solid( font, ptInfo, textColor);
        SDL_BlitSurface(message, NULL, windowSurface, &postText);
        SDL_FreeSurface(message);
        
        postText.x = 150;
        postText.y = 15;
        sprintf(ptNum, "%ld", human->getNumTerritories());
        message = TTF_RenderText_Solid( font, ptNum, textColor);
        SDL_BlitSurface(message, NULL, windowSurface, &postText);
        SDL_FreeSurface(message);

        postText.x = 40;
        postText.y = 28;
        textColor = { 0, 0, 255 };
        message = TTF_RenderText_Solid( font, reinforceInfo, textColor);
        SDL_BlitSurface(message, NULL, windowSurface, &postText);
        SDL_FreeSurface(message);
        
        postText.x = 155;
        postText.y = 28;
        sprintf(pReinforce, "%d", human->getReinforcements());
        message = TTF_RenderText_Solid( font, pReinforce, textColor);
        SDL_BlitSurface(message, NULL, windowSurface, &postText);
        SDL_FreeSurface(message);
        
        //These next few are for the bottom info
        postText.x = 300;
        postText.y = 560;
        textColor = { 0, 0, 0 };
        message = TTF_RenderText_Solid( font, phaseText, textColor);
        SDL_BlitSurface(message, NULL, windowSurface, &postText);
        SDL_FreeSurface(message);
        
        postText.x = 415;
        postText.y = 560;
        textColor = { 0, 0, 0 };
        for (int i = 0; i < sizeof(phaseDisplay); i++)
        {
            phaseDisplay[i] = '\0';
        }
        for (int i = 0; i < currTurn.length(); i++)
        {
            phaseDisplay[i] = currTurn[i];
        }
        message = TTF_RenderText_Solid( font, phaseDisplay, textColor);
        SDL_BlitSurface(message, NULL, windowSurface, &postText);
        SDL_FreeSurface(message);
        
        postText.x = 300;
        postText.y = 570;
        textColor = { 0, 0, 0 };
        message = TTF_RenderText_Solid( font, click1Text, textColor);
        SDL_BlitSurface(message, NULL, windowSurface, &postText);
        SDL_FreeSurface(message);

        postText.x = 415;
        postText.y = 570;
        textColor = { 0, 0, 0 };
        for (int i = 0; i < sizeof(click1Display); i++)
        {
            click1Display[i] = '\0';
        }
        for (int i = 0; i < click1.length(); i++)
        {
            click1Display[i] = click1[i];
        }
        message = TTF_RenderText_Solid( font, click1Display, textColor);
        SDL_BlitSurface(message, NULL, windowSurface, &postText);
        SDL_FreeSurface(message);
        
        postText.x = 300;
        postText.y = 580;
        textColor = { 0, 0, 0 };
        message = TTF_RenderText_Solid( font, click2Text, textColor);
        SDL_BlitSurface(message, NULL, windowSurface, &postText);
        SDL_FreeSurface(message);
        
        postText.x = 415;
        postText.y = 580;
        textColor = { 0, 0, 0 };
        for (int i = 0; i < sizeof(click2Display); i++)
        {
            click2Display[i] = '\0';
        }
        for (int i = 0; i < click2.length(); i++)
        {
            click2Display[i] = click2[i];
        }
        message = TTF_RenderText_Solid( font, click2Display, textColor);
        SDL_BlitSurface(message, NULL, windowSurface, &postText);
        SDL_FreeSurface(message);
        //This section is testing how to orchestrate turn order
        if (currTurn == "initial")
        {
            if (human->getOnce())
                human->setReinforcements((25 - human->getNumTerritories()));
            
        }
        
        //This section is testing how to get the army values on the board
        for (int i = 0; i < 42; i++)
        {
            value = value.findTerritory(i, territories);
            sprintf(text, "%d", value.getArmyValue());
            textColor = ownerColor(value);
            message = TTF_RenderText_Solid( font, text, textColor);
            
            postText = getPosition(i);
            SDL_BlitSurface(message, NULL, windowSurface, &postText);
            SDL_FreeSurface(message);
        }
        
        
        SDL_UpdateWindowSurface(window);
    }
    
    SDL_FreeSurface(imageSurface);
    SDL_FreeSurface(windowSurface);
    SDL_FreeSurface(message);
    
    imageSurface = NULL;
    windowSurface = NULL;
    message = NULL;
    
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return;
}

/*********************************************************************
 * -owner color will return the correct color for the given player
 *********************************************************************/
SDL_Color Game::ownerColor(Territory value){
    SDL_Color textColor = { 0, 0, 0 };
    
    if (value.getOwner() == "Human")
        textColor = { 0, 0, 255 };
    else if (value.getOwner() == "bot1")
        textColor = { 255, 0, 0 };
    else if (value.getOwner() == "bot2")
        textColor = { 255, 145, 0 };
    else if (value.getOwner() == "bot3")
        textColor = { 61, 162, 132 };
    else if (value.getOwner() == "bot4")
        textColor = { 166, 3, 112 };
    
    return textColor;
}

/*********************************************************************
 * -getPosition will return the given territory's position for displaying
 *  the number of armies in that territory
 *********************************************************************/
SDL_Rect Game::getPosition(int i){
    SDL_Rect pos;
    
    if (i == 0)
    {
        pos.x = 45;
        pos.y = 110;
    }
    else if (i == 1)
    {
        pos.x = 110;
        pos.y = 110;
    }
    else if (i == 2)
    {
        pos.x = 275;
        pos.y = 110;
    }
    else if (i == 3)
    {
        pos.x = 120;
        pos.y = 180;
    }
    else if (i == 4)
    {
        pos.x = 175;
        pos.y = 165;
    }

    else if (i == 5)
    {
        pos.x = 222;
        pos.y = 155;
    }

    else if (i == 6)
    {
        pos.x = 117;
        pos.y = 245;
    }

    else if (i == 7)
    {
        pos.x = 160;
        pos.y = 245;
    }

    else if (i == 8)
    {
        pos.x = 140;
        pos.y = 295;
    }

    else if (i == 9)
    {
        pos.x = 175;
        pos.y = 338;
    }

    else if (i == 10)
    {
        pos.x = 175;
        pos.y = 385;
    }

    else if (i == 11)
    {
        pos.x = 200;
        pos.y = 425;
    }

    else if (i == 12)
    {
        pos.x = 250;
        pos.y = 385;
    }

    else if (i == 13)
    {
        pos.x = 360;
        pos.y = 380;
    }

    else if (i == 14)
    {
        pos.x = 430;
        pos.y = 405;
    }

    else if (i == 15)
    {
        pos.x = 430;
        pos.y = 495;
    }

    else if (i == 16)
    {
        pos.x = 503;
        pos.y = 478;
    }

    else if (i == 17)
    {
        pos.x = 480;
        pos.y = 400;
    }

    else if (i == 18)
    {
        pos.x = 440;
        pos.y = 345;
    }

    else if (i == 19)
    {
        pos.x = 350;
        pos.y = 260;
    }

    else if (i == 20)
    {
        pos.x = 330;
        pos.y = 190;
    }

    else if (i == 21)
    {
        pos.x = 340;
        pos.y = 157;
    }
    else if (i == 22)
    {
        pos.x = 385;
        pos.y = 230;
    }

    else if (i == 23)
    {
        pos.x = 395;
        pos.y = 275;
    }

    else if (i == 24)
    {
        pos.x = 400;
        pos.y = 165;
    }
    else if (i == 25)
    {
        pos.x = 465;
        pos.y = 190;
    }
    else if (i == 26)
    {
        pos.x = 490;
        pos.y = 310;
    }

    else if (i == 27)
    {
        pos.x = 550;
        pos.y = 250;
    }
    else if (i == 28)
    {
        pos.x = 560;
        pos.y = 185;
    }
    else if (i == 29)
    {
        pos.x = 600;
        pos.y = 120;
    }
    else if (i == 30)
    {
        pos.x = 660;
        pos.y = 115;
    }
    else if (i == 31)
    {
        pos.x = 720;
        pos.y = 115;
    }
    else if (i == 32)
    {
        pos.x = 665;
        pos.y = 155;
    }
    else if (i == 33)
    {
        pos.x = 665;
        pos.y = 198;
    }
    else if (i == 34)
    {
        pos.x = 750;
        pos.y = 200;
    }
    else if (i == 35)
    {
        pos.x = 650;
        pos.y = 275;
    }
    else if (i == 36)
    {
        pos.x = 580;
        pos.y = 285;
    }
    else if (i == 37)
    {
        pos.x = 650;
        pos.y = 303;

    }
    else if (i == 38)
    {
        pos.x = 655;
        pos.y = 375;
    }
    else if (i == 39)
    {
        pos.x = 715;
        pos.y = 380;
    }
    else if (i == 40)
    {
        pos.x = 675;
        pos.y = 435;
    }
    else if (i == 41)
    {
        pos.x = 745;
        pos.y = 460;    }
   else
   {
       pos.x = 0;
       pos.y = 0;
       std::cout << "Error in getPosition\n";
   }
    
    return pos;
}

/*********************************************************************
 * -getClickPos will determin if a click was in a territory and handle
 *  current turn order accordingly
 *********************************************************************/
void Game::getClickPos(int x, int y, std::string currTurn, std::list<Territory> &masterList,
                       std::string &click1, std::string &click2)
{
    std::list<Territory>::iterator it = masterList.begin();
    
    if(x > 40 && y > 100 &&
       x < 70 && y < 150) //Alaska
    {
        if(currTurn == "initial" || currTurn == "reinforce") //This if section will handle the reinforcement phase
        {
            if(it->getOwner() == "Human")                    //as long as the territory belongs to the human player
            {                                                // a reinforcement point will be added
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")                       //This section will handle the battle phase
        {
            if (click1 == "" && (it->getOwner() == "Human")) //if it is the first click and human
            {
                click1 = "Alaska";                           //Set click one to that territory
            }
            else if (click1 == "Alaska")                     //click again to deselect
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Alaska";                           //if click one is selected and the next click is in a connected
            }                                                //territory, then that becomes click2
        }
    }
    else if (x > 85 && y > 110
             && x < 170 && y < 145) //Northwest Territory
    {
        it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Northwest Territory";
            }
            else if (click1 == "Northwest Territory")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Northwest Territory";
            }
        }
    }
    else if (x > 270 && y > 70
             && x < 315 && y < 170) // Greenland
    {
        it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Greenland";
            }
            else if (click1 == "Greenland")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Greenland";
            }
        }
    }
    else if (x > 85 && y > 155
             && x < 140 && y < 190) //Alberta
    {
        it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Alberta";
            }
            else if (click1 == "Alberta")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Alberta";
            }
        }
    }
    else if (x > 160 && y > 155
             && x < 200 && y < 190) //Ontario
    {
        it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Ontario";
            }
            else if (click1 == "Ontario")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Ontario";
            }
        }
    }
    else if (x > 220 && y > 155
             && x < 260 && y < 190) //Eastern Canada
    {
        it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Eastern Canada";
            }
            else if (click1 == "Eastern Canada")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Eastern Canada";
            }
        }
    }
    else if (x > 90 && y > 210
             && x < 140 && y < 250) //Western United States
    {
        it++; it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Western United States";
            }
            else if (click1 == "Western United States")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Western United States";
            }
        }
    }
    else if (x > 170 && y > 230
             && x < 210 && y < 270) //Eastern United States
    {
        it++; it++; it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Eastern United States";
            }
            else if (click1 == "Eastern United States")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Eastern United States";
            }
        }
    }
    else if (x > 100 && y > 270
             && x < 150 && y < 330) //Central America
    {
        it++; it++; it++; it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Central America";
            }
            else if (click1 == "Central America")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Central America";
            }
        }
    }
    else if (x > 170 && y > 315
             && x < 210 && y < 350) //Venezuala
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Venezuala";
            }
            else if (click1 == "Venezuala")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Venezuala";
            }
        }
    }
    else if (x > 175 && y > 390
             && x < 215 && y < 420) //Peru
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Peru";
            }
            else if (click1 == "Peru")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Peru";
            }
        }
    }
    else if (x > 200 && y > 430
             && x < 250 && y < 500) //Argentina
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Argentina";
            }
            else if (click1 == "Argentina")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Argentina";
            }
        }
    }
    else if (x > 240 && y > 300
             && x < 300 && y < 450) //Brazil
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Brazil";
            }
            else if (click1 == "Brazil")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Brazil";
            }
        }
    }
    else if (x > 350 && y > 320
             && x < 410 && y < 400) //North Africa
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "North Africa";
            }
            else if (click1 == "North Africa")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "North Africa";
            }
        }
    }
    else if (x > 410 && y > 400
             && x < 450 && y < 460) //Central Africa
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Central Africa";
            }
            else if (click1 == "Central Africa")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Central Africa";
            }
        }
        
    }
    else if (x > 410 && y > 470
             && x < 450 && y < 530) //South Africa
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "South Africa";
            }
            else if (click1 == "South Africa")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "South Africa";
            }
        }
        
    }
    else if (x > 500 && y > 460
             && x < 530 && y < 500) //Madagascar
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Madagascar";
            }
            else if (click1 == "Madagascar")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Madagascar";
            }
        }
    }
    else if (x > 445 && y > 365
             && x < 500 && y < 400) //East Africa
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "East Africa";
            }
            else if (click1 == "East Africa")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "East Africa";
            }
        }
    }
    else if (x > 410 && y > 320
             && x < 480 && y < 360) //Egypt
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Egypt";
            }
            else if (click1 == "Egypt")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Egypt";
            }
        }
    }
    else if (x > 330 && y > 250
             && x < 380 && y < 300) //Western Europe
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Western Europe";
            }
            else if (click1 == "Western Europe")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Western Europe";
            }
        }
    }
    else if (x > 310 && y > 180
             && x < 350 && y < 230) //Great Britian
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Great Britian";
            }
            else if (click1 == "Great Britian")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Great Britian";
            }
        }
    }
    else if (x > 330 && y > 135
             && x < 370 && y < 170) //Iceland
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Iceland";
            }
            else if (click1 == "Iceland")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Iceland";
            }
        }
    }
    else if (x > 400 && y > 130
             && x < 450 && y < 170) //Scandinavia
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Scandinavia";
            }
            else if (click1 == "Scandinavia")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Scandinavia";
            }
        }
    }
    else if (x > 395 && y > 205
             && x < 445 && y < 250) //Northern Europe
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Northern Europe";
            }
            else if (click1 == "Northern Europe")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Northern Europe";
            }
        }
    }
    else if (x > 395 && y > 265
             && x < 445 && y < 300) //Southern Europe
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Southern Europe";
            }
            else if (click1 == "Southern Europe")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Southern Europe";
            }
        }
    }
    else if (x > 450 && y > 140
             && x < 500 && y < 250) //Russia
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Russia";
            }
            else if (click1 == "Russia")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Russia";
            }
        }
    }
    else if (x > 475 && y > 280
             && x < 530 && y < 370) //Middle East
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Middle East";
            }
            else if (click1 == "Middle East")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Middle East";
            }
        }
    }
    else if (x > 520 && y > 190
             && x < 570 && y < 260) //Afghanistan
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Afghanistan";
            }
            else if (click1 == "Afghanistan")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Afghanistan";
            }
        }
    }
    else if (x > 550 && y > 120
             && x < 580 && y < 200) //Ural
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Ural";
            }
            else if (click1 == "Ural")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Ural";
            }
        }
    }
    else if (x > 590 && y > 100
             && x < 630 && y < 170) //Siberia
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Siberia";
            }
            else if (click1 == "Siberia")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Siberia";
            }
        }
    }
    else if (x > 650 && y > 90
             && x < 690 && y < 140) //Yakutsk
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        
       if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
       else if (currTurn == "battle")
       {
           if (click1 == "" && (it->getOwner() == "Human"))
           {
               click1 = "Yakutsk";
           }
           else if (click1 == "Yakutsk")
           {
               click1 = "";
               click2 = "";
           }
           else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
           {
               click2 = "Yakutsk";
           }
       }
    }
    else if (x > 700 && y > 90
             && x < 780 && y < 140) //Kamchatka
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Kamchatka";
            }
            else if (click1 == "Kamchatka")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Kamchatka";
            }
        }
    }
    else if (x > 650 && y > 150
             && x < 690 && y < 190) //Irkutsk
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Irkutsk";
            }
            else if (click1 == "Irkutsk")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Irkutsk";
            }
        }
    }
    else if (x > 630 && y > 200
             && x < 700 && y < 240) //Mongolia
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Mongolia";
            }
            else if (click1 == "Mongolia")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Mongolia";
            }
        }
    }
    else if (x > 730 && y > 200
             && x < 760 && y < 240) //Japan
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Japan";
            }
            else if (click1 == "Japan")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Japan";
            }
        }
    }
    else if (x > 600 && y > 235
             && x < 700 && y < 285) //China
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "China";
            }
            else if (click1 == "China")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "China";
            }
        }
    }
    else if (x > 560 && y > 280
             && x < 630 && y < 340) //India
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "India";
            }
            else if (click1 == "India")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "India";
            }
        }
    }
    else if (x > 640 && y > 300
             && x < 680 && y < 360) //Southeast Asia
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Southeast Asia";
            }
            else if (click1 == "Southeast Asia")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Southeast Asia";
            }
        }
    }
    else if (x > 620 && y > 380
             && x < 680 && y < 420) //Indonesia
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Indonesia";
            }
            else if (click1 == "Indonesia")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Indonesia";
            }
        }
    }
    else if (x > 700 && y > 360
             && x < 760 && y < 400) //New Guinea
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "New Guinea";
            }
            else if (click1 == "New Guinea")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "New Guinea";
            }
        }
    }
    else if (x > 650 && y > 430
             && x < 710 && y < 480) //Western Australia
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Western Australia";
            }
            else if (click1 == "Western Australia")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Western Australia";
            }
        }
    }
    else if (x > 720 && y > 430
             && x < 780 && y < 480) //Eastern Australia
    {
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++; it++; it++; it++; it++; it++; it++; it++; it++; it++;
        it++;
        
        if(currTurn == "initial" || currTurn == "reinforce")
        {
            if(it->getOwner() == "Human")
            {
                it->setArmyValue((it->getArmyValue() + 1));
                human->setReinforcements(human->getReinforcements() - 1);
            }
        }
        else if (currTurn == "battle")
        {
            if (click1 == "" && (it->getOwner() == "Human"))
            {
                click1 = "Eastern Australia";
            }
            else if (click1 == "Eastern Australia")
            {
                click1 = "";
                click2 = "";
            }
            else if (click1 != "" && (it->getOwner() != "Human") && it->isConnectedTo(click1))
            {
                click2 = "Eastern Australia";
            }
        }
    }
    
    if (currTurn == "battle" && click2 != "")
    {
        battle.fightBattle(masterList, click1, click2);
        click1 = "";
        click2 = "";
    }
}

