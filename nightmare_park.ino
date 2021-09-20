/*  Nightmare Park
    Arduboy port by Tom Millichamp 2021
    based on the old Commodore PET game
    by Bob Chappell from 1980
*/

//TODO - make the park bigger so heart fits on it better

#include <Arduboy2.h>
Arduboy2 arduboy;

enum class GameState : uint8_t
{
  Title,
  Gameplay,
};
GameState gameState;

enum class Baddies : uint8_t
{
  Najjers,
  Blabbers,
  Unicorns,
  Stingers,
  Lurgi,
  Zigzaggers,
};
//Baddies baddies;

//Global Variables
int8_t lives;
int8_t player_x,player_y;
int8_t win=1,lose=0;
int8_t rnd_game=0;
int8_t rnd_step=0;
bool moved=false;

//Graphics
#include "graphics.h"
#include "functions.h"
#include "mini_games.h"

void setup()
{
	arduboy.begin(); // initialize Arduboy
    lives = 3;
    player_x = 10;
    player_y = 30;
    gameState=GameState::Title;
}

void loop()
{
	if (!arduboy.nextFrame())
        return;

    switch (gameState)
    {
        case GameState::Title:
            arduboy.clear();
            arduboy.print(F(" !!NIGHTMARE PARK!!")); 
            arduboy.print(F("\n THE SHORTEST ROUTE"));
            arduboy.print(F("\n MAY NOT BE THE BEST")); 
            arduboy.print(F("\n ONLY MOVE N,S OR E")); 
            arduboy.print(F("\n STAY ON THE PATH")); 
            arduboy.print(F("\nPress A to Start"));
            arduboy.display();
            arduboy.pollButtons();
            if (arduboy.justPressed(A_BUTTON)){
                gameState=GameState::Gameplay;
            }
        break;

        case GameState::Gameplay:
            arduboy.clear();
            //Draw number of lives left (hearts)
            for (int8_t i=1;i<=lives;i++){
                Sprites::drawOverwrite(90+((i*8)+2),52,heart,0); //heart icon for lives
            }
            arduboy.print(F("N,S,E?"));
            //Draw Park 96 x 48 pixels
            arduboy.drawBitmap(10,12,park,108,48,WHITE);
            //add text
            arduboy.setCursor(0,22);
            arduboy.print(F("IN"));
            arduboy.setCursor(110,30);
            arduboy.print(F("OUT"));
            //Draw person
            Sprites::drawOverwrite(player_x,player_y,player,0);
            
            moved=false;
            //check for player moving
            arduboy.pollButtons();
            if (arduboy.justPressed(UP_BUTTON)) {player_y-=6;moved=true;}
            if (arduboy.justPressed(DOWN_BUTTON)) {player_y+=6;moved=true;}
            if (arduboy.justPressed(RIGHT_BUTTON)) {player_x+=6;moved=true;}

            //check if we escaped!
            if (player_x > 116){
                delay(250);
                arduboy.clear();
                arduboy.print(F("\nWELL DONE!!!"));
                arduboy.print(F("\nYou beat the Park"));
                arduboy.print(F("\nBut next time...!"));
                arduboy.display();
                delay(3000);
                setup();
                break;
            }
            //check if we have strayed from the path!
            if (arduboy.getPixel(player_x+3,player_y+3)==BLACK){
                delay(250);
                arduboy.clear();
                arduboy.print(F("\nFell into the Abyss"));
                arduboy.print(F("\nBack to the Start!"));
                arduboy.display();
                delay(3000);
                player_x = 10; player_y = 30;
                break;
            }

            //throw a random mini game if the player moved
            if (moved){
                miniGame();
            }
        break;
    }

    arduboy.display();
} //end of main loop



//Call mini games if player moved
void miniGame(){
    //random mini-games
    arduboy.initRandomSeed();
    rnd_step = random(1, 6);
    if (rnd_step < 3){
        int8_t outcome = lose;
        rnd_game = random(1, 15);
        switch (rnd_game)
        {
        case 1: outcome=stampeding(Baddies::Unicorns);break;
        case 2: outcome=stampeding(Baddies::Stingers);break;
        case 3: outcome=mathematician(); break;
        case 4: outcome=death_rays(); break;
        case 5: outcome=multiplying(Baddies::Lurgi); break;
        case 6: outcome=multiplying(Baddies::Zigzaggers); break;
        case 7: outcome=crusher(); break;
        case 8: outcome=barbs(); break;
        case 9: outcome=gorilla();break;
        case 10: outcome=doors();break;
        case 11: outcome=surrounded(Baddies::Blabbers);break;
        case 12: outcome=surrounded(Baddies::Najjers);break;
        case 13: outcome=gambler();break;
        case 14: outcome=backtostart();break;
        default:
            break;
        }

        //check win or lose
        if (outcome==lose){
            lives--;
        }

        //check if we still have lives!
        if (lives==0){
            delay(250);
            arduboy.clear();
            arduboy.print(F("DEAD!!!"));
            arduboy.print(F("\nNo more lives"));
            arduboy.print(F("\nBeaten by the Park"));
            arduboy.print(F("\nTry again...!"));
            arduboy.display();
            delay(3000);
            setup();
        }

    }
    return;
}

