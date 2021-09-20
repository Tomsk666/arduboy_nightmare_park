// Mini-games:
int8_t stampeding(Baddies baddy_type){
    //Stampeding Unicorns - letter pi - $5E
    //Stampeding Stingers - Up arrow $1E
    arduboy.clear();
    arduboy.print(F("Stampeding "));
    if(baddy_type == Baddies::Stingers){arduboy.print(F("Stingers"));}
    else{arduboy.print(F("Unicorns"));}
    arduboy.print(F("\nuse Left & Right"));
    arduboy.print(F("\nto survive!"));
    arduboy.display();
    delay(3000);

    //create Rect arrays for baddies & player heart
    int8_t bad_row=57,play_x=64,play_dead=0;
    Rect rBaddies[15];
    Rect rPlayer{64,0,8,7};

    for(int8_t num_bad=0;num_bad<15;num_bad++){
            rBaddies[num_bad].x=random(0, 120);
            rBaddies[num_bad].y=57;
            rBaddies[num_bad].width=5;
            rBaddies[num_bad].height=7;
    }

    arduboy.clear();
    //loop for 5 rows of baddies 10 times going up the screen
    for (int8_t i=0;i<10;i++){ 

        //loop for each row & draw baddies
        for (int8_t bad=0;bad<3;bad++){
            rBaddies[bad].y=bad_row;
            if(baddy_type == Baddies::Stingers){Sprites::drawOverwrite(rBaddies[bad].x,rBaddies[bad].y,stinger,0);}
            else{Sprites::drawOverwrite(rBaddies[bad].x,rBaddies[bad].y,unicorn,0);}
        }
        for (int8_t bad=3;bad<6;bad++){
            rBaddies[bad].y=bad_row+10;
            if (bad_row<65){
                if(baddy_type == Baddies::Stingers){Sprites::drawOverwrite(rBaddies[bad].x,rBaddies[bad].y,stinger,0);}
                else{Sprites::drawOverwrite(rBaddies[bad].x,rBaddies[bad].y,unicorn,0);}
            }
        }
        for (int8_t bad=6;bad<9;bad++){
            rBaddies[bad].y=bad_row+25;
            if (bad_row<65){
                if(baddy_type == Baddies::Stingers){Sprites::drawOverwrite(rBaddies[bad].x,rBaddies[bad].y,stinger,0);}
                else{Sprites::drawOverwrite(rBaddies[bad].x,rBaddies[bad].y,unicorn,0);}
            }
        }
        for (int8_t bad=9;bad<12;bad++){
            rBaddies[bad].y=bad_row+40;
            if (bad_row<65){
                if(baddy_type == Baddies::Stingers){Sprites::drawOverwrite(rBaddies[bad].x,rBaddies[bad].y,stinger,0);}
                else{Sprites::drawOverwrite(rBaddies[bad].x,rBaddies[bad].y,unicorn,0);}
            }
        }
        for (int8_t bad=12;bad<15;bad++){
            rBaddies[bad].y=bad_row+55;
            if (bad_row<65){
                if(baddy_type == Baddies::Stingers){Sprites::drawOverwrite(rBaddies[bad].x,rBaddies[bad].y,stinger,0);}
                else{Sprites::drawOverwrite(rBaddies[bad].x,rBaddies[bad].y,unicorn,0);}
            }
        }
        //check if killed:
        for (int8_t num_bad=0;num_bad<15;num_bad++){
            if (Arduboy2::collide(rBaddies[num_bad],rPlayer)){
                play_dead=1;
            }
        }

        if (play_dead==1){break;}

        bad_row-=14; //move baddies up a row

        //now we have a 1 second delay before baddies move up a row
        //but player can still move in that second time frame
        //so I split it into 5 x 200msec
        for (int8_t del=1;del<9;del++){
            //draw player    
            Sprites::drawOverwrite(play_x,0,heart,0);
            rPlayer.x=play_x;
            //player move
            arduboy.pollButtons();
            if (arduboy.justPressed(LEFT_BUTTON) && play_x>=8){  
                Sprites::drawOverwrite(play_x,0,blank_square,0);
                arduboy.display(); 
                play_x-=8;
            }
            if (arduboy.justPressed(RIGHT_BUTTON) && play_x<=112){
                Sprites::drawOverwrite(play_x,0,blank_square,0);
                arduboy.display();
                play_x+=8;
            }
            arduboy.display();
            delay(100);
        }
        arduboy.clear();
    }
    if (play_dead==1){
        lose_text("\n\nTRAMPLED!!");
        return lose;
    }

    win_text("\n\nSURVIVED!!");
    return win;
}
int8_t mathematician(){
    //The Mad Mathematician
    unsigned long startTime = millis();
    unsigned long currTime;
    int8_t guess=20;
    arduboy.initRandomSeed();
    int8_t numa = random(1, 11),numb = random(1, 11),numc = random(1, 11),numd = random(1, 11);
    int8_t numtotal=numa+numb+numc+numd;

    arduboy.clear();
    arduboy.print(F("Mad Mathematician!"));
    arduboy.print(F("\n15 secs to answer"));
    arduboy.print(F("\nUse up & down"));
    arduboy.print(F("\npress A to answer"));
    arduboy.display();
    delay(5000);

    do{
        arduboy.clear();
        currTime = millis();
        if((currTime-startTime) > 15000){
            break;
        }
        //display timer
        arduboy.print(F("Time : "));
        arduboy.print((currTime-startTime)/1000);
        //print the numbers to add
        arduboy.print(F("\nAdd these:\n\n"));
        arduboy.print(numa);arduboy.print(F("+"));
        arduboy.print(numb);arduboy.print(F("+"));
        arduboy.print(numc);arduboy.print(F("+"));
        arduboy.print(numd);
        //display their guess
        arduboy.print(F("\n\n        \x1E\nAnswer: "));
        arduboy.print(guess);
        arduboy.print(F("\n        \x1F"));
        arduboy.display();
        arduboy.pollButtons();
        if (arduboy.justPressed(UP_BUTTON)){
            guess++;
        }
        if (arduboy.justPressed(DOWN_BUTTON)){
            guess--;
        }
    } while (!arduboy.justPressed(A_BUTTON));
    if (guess==numtotal){
        win_text("\n\nCORRECT!!");
        return win;
    }
    lose_text("\n\nWRONG!!");
    return lose;
}
int8_t death_rays(){
    //Death Rayys
    bool player_hit=false;
    arduboy.clear();
    arduboy.print(F("Death Rays!"));
    arduboy.print(F("\nKeep still"));
    arduboy.print(F("\nand hope!!"));
    arduboy.display();
    delay(3000);
    arduboy.clear();
    //draw player
    Sprites::drawOverwrite(64,57,heart,0);
    arduboy.initRandomSeed();
    for (int8_t i=1;i<8;i++){
        int8_t rnd_top = random(0,128);
        int8_t rnd_bottom = random(0,128);
        arduboy.drawLine(rnd_top,0,rnd_bottom,62);
        delay(750);
        arduboy.display();
        if (rnd_bottom>64 && rnd_bottom<72){
            player_hit=true;
            delay(1000);
            break;
        }
    }
    if (player_hit){
        lose_text("\n\nKilled!");
        return lose;
    }

    win_text("\n\nLucky!!");
    return win;
}
int8_t multiplying(Baddies baddy_type){
    //Multiplying Lurgi - asterix $2A
    //Multiplying Zigzaggers - letter 'Z' $1A
    arduboy.clear();
    arduboy.print(F("    Multiplying\n"));
    if(baddy_type == Baddies::Zigzaggers){arduboy.print(F("    Zigzaggers"));}
    else{arduboy.print(F("    Lurgi"));}
    arduboy.print(F("\n\n  1 min. to reach"));
    arduboy.print(F("\n  the exit!"));
    arduboy.display();
    delay(3000);

    int8_t play_x=64,play_y=32,play_dead=0,moves=0,baddie_x=0,baddie_y=0;
    arduboy.initRandomSeed();
    arduboy.clear();

    while (play_dead==0){
        //draw player in middle of screen
        Sprites::drawOverwrite(play_x,play_y,player,0);

        //player move
        arduboy.pollButtons();
        if (arduboy.justPressed(LEFT_BUTTON) && play_x>=8){  
            Sprites::drawOverwrite(play_x,play_y,blank8,0);
            arduboy.display(); 
            play_x-=8;
            moves++;
        }
        if (arduboy.justPressed(RIGHT_BUTTON) && play_x<=112){
            Sprites::drawOverwrite(play_x,play_y,blank8,0);
            arduboy.display();
            play_x+=8;
            moves++;
        }
        if (arduboy.justPressed(UP_BUTTON) && play_y>=8){  
            Sprites::drawOverwrite(play_x,play_y,blank8,0);
            arduboy.display(); 
            play_y-=8;
            moves++;
        }
        if (arduboy.justPressed(DOWN_BUTTON) && play_y<=48){
            Sprites::drawOverwrite(play_x,play_y,blank8,0);
            arduboy.display();
            play_y+=8;
            moves++;
        }

        //Check for win
        if (play_x==0 && play_y==0){
            delay(250);
            break;
        }
        //check for death!
        if (arduboy.getPixel(play_x,play_y)==WHITE){
            delay(250);
            play_dead=1;
            break;
        }

        //create baddies
        if (moves==3){
            moves=0;
            for (int8_t x=1;x<8;x++){
                baddie_x=random(0,15)*8; //factors of 8 to keep them in line with player size 8 pxls
                baddie_y=random(0,7)*8;
                if (baddie_x!=play_x && baddie_y!=play_y){
                    if (baddy_type == Baddies::Lurgi){
                        Sprites::drawOverwrite(baddie_x,baddie_y,lurgi,0);
                    }
                    else{
                        Sprites::drawOverwrite(baddie_x,baddie_y,zigzagger,0);
                    }
                }
            }
        }
        Sprites::drawOverwrite(0,0,blank8,0);
        arduboy.setCursor(0,0);
        arduboy.print(F("E"));
        arduboy.display();
    }
    if (play_dead==1){
        lose_text("\n\nSmitten by\na monster");
        return lose;
    }

    win_text("\n\nEscaped!!");
    return win;
}
int8_t crusher(){
    //Crusher
    arduboy.clear();
    arduboy.print(F("Crusher!"));
    arduboy.print(F("\nOnly 1 button"));
    arduboy.print(F("\nwill stop it!!"));
    arduboy.display();
    delay(3000);

    arduboy.initRandomSeed();
    int8_t rnd_btn = random(1,7);
    int8_t guesses=1,keyPressed=0,start_y=0;

    arduboy.clear();
    Sprites::drawOverwrite(64,57,heart,0);
    arduboy.display();
    
    while (guesses<5){
        bool btnPress=false;
        int8_t keyPressed=0;
        do{
            arduboy.pollButtons();
            if (arduboy.justPressed(UP_BUTTON)){keyPressed=1;btnPress=true;}
            else if (arduboy.justPressed(DOWN_BUTTON)){keyPressed=2;btnPress=true;}
            else if (arduboy.justPressed(LEFT_BUTTON)){keyPressed=3;btnPress=true;}
            else if (arduboy.justPressed(RIGHT_BUTTON)){keyPressed=4;btnPress=true;}
            else if (arduboy.justPressed(A_BUTTON)){keyPressed=5;btnPress=true;}
            else if (arduboy.justPressed(B_BUTTON)){keyPressed=6;btnPress=true;}
        }while (!btnPress);

        if(keyPressed==rnd_btn){
            win_text("\n\nLucky!");
            return win;
        }
        else{
            if (guesses>1){
                start_y+=16;
                }
            arduboy.fillRect(20,start_y,88,16,WHITE);
            guesses++;
        }
        arduboy.display();
    }
    delay(500);
    lose_text("\n\nSquashed!!");
    return lose;
}
int8_t barbs(){
    //Hail of Barbs
    arduboy.clear();
    arduboy.print(F("Hail of Barbs!"));
    arduboy.print(F("\nKeep still and"));
    arduboy.print(F("\ncross your fingers"));
    arduboy.display();
    delay(3000);

    int8_t play_x=64,play_y=48,play_dead=0;
    arduboy.initRandomSeed();
    arduboy.clear();

    //draw player on screen
    Sprites::drawOverwrite(play_x,play_y,player,0);
    arduboy.display();
    //create the hail of barbs
    //7 rows of barbs to fill the screen
    for (int8_t barb_y=0;barb_y<=56;barb_y+=8){
        // 3 barbs on each row
        for (int8_t barb_loop=1;barb_loop<4;barb_loop++){
            int8_t barb_x=random(0,15)*8;
            Sprites::drawOverwrite(barb_x,barb_y,barb,0);
            
            if (barb_x==play_x && barb_y==play_y){
                play_dead=1;
            }
        }
        arduboy.display();
        delay(1000);
    }
    if (play_dead==1){
        delay(1000);
        lose_text("\n\nExterminated!");
        return lose;
    }
    delay(500);
    lose_text("\n\nMissed!!");
    return win;
}

int8_t gorilla(){
    //The Egotistical Gorilla
    arduboy.clear();
    arduboy.print(F("Egotistical Gorilla!"));
    arduboy.print(F("\nTell him his name"));
    arduboy.print(F("\nor be dismantled"));
    arduboy.display();
    arduboy.print("\nmore   \x1F");//down arrow
    arduboy.display();
    wait_for_key_press(DOWN_BUTTON);
    arduboy.clear();
    arduboy.print(F("the name will"));
    arduboy.print(F("\nappear in a flash"));
    arduboy.print(F("\nof lightning!"));
    arduboy.print(F("\nPress A to Start"));
    arduboy.display();
    wait_for_key_press(A_BUTTON);
    delay(2000);
    arduboy.clear();

    String names[]={"Clarence","Percival","Stanley","Winston"};
    arduboy.initRandomSeed();
    int8_t rnd_name=random(0,4);
    //falsh the name
    arduboy.setCursor(32,32);
    arduboy.print(names[rnd_name]);
    arduboy.display();
    delay(150);
    arduboy.clear();
    arduboy.display();
    delay(1000);

    int8_t select=0;
    do{
        arduboy.clear();
        arduboy.print(F("Choose his name\n"));
        arduboy.print(F("\n   Clarence"));
        arduboy.print(F("\n   Percival"));
        arduboy.print(F("\n   Stanley"));
        arduboy.print(F("\n   Winston"));
        
        arduboy.pollButtons();
        if (arduboy.justPressed(UP_BUTTON)){
            if (select>0){select--;}
        }
        if (arduboy.justPressed(DOWN_BUTTON)){
            if (select<3){select++;}
        }
        switch (select)
        {
        case 0: arduboy.setCursor(0,16); break;
        case 1: arduboy.setCursor(0,24); break;
        case 2: arduboy.setCursor(0,32); break;
        case 3: arduboy.setCursor(0,40); break;
        }
        arduboy.print("\x10"); //right arrow
        arduboy.display();
    }while (!arduboy.justPressed(A_BUTTON));

    if (select==rnd_name){
        win_text("\n\nCorrect!!");
        return win;
    }

    lose_text("\n\nWRONG!!!");
    return lose;
}
int8_t doors(){
    //The Doors
    arduboy.initRandomSeed();
    int8_t chooser=2;
    int8_t chooser_loc=62;
    int8_t rnd_door = random(1, 4);
    int8_t door_pos=0;
    switch (rnd_door)
    {
    case 1:
        door_pos=10;break;
    case 2:
        door_pos=50;break;
    case 3:
        door_pos=90;break;
    }

    arduboy.clear();
    arduboy.print(F("The Doors!"));
    arduboy.print(F("\nbehind one is a"));
    arduboy.print(F("\nstarving lion!"));
    arduboy.print(F("\nL & R to choose"));
    arduboy.display();
    delay(3000);
    arduboy.clear();
    for (int8_t i=0;i<50;i+=10){
        arduboy.drawBitmap(10,i,door,25,10,WHITE);
        arduboy.drawBitmap(50,i,door,25,10,WHITE);
        arduboy.drawBitmap(90,i,door,25,10,WHITE);
        arduboy.display();
        delay(500);   
    }
    //draw the chooser
    do{
        switch (chooser)
        {
        case 1: chooser_loc = 22;break;
        case 2: chooser_loc = 62;break;
        case 3: chooser_loc = 102;break;
        }
        arduboy.setCursor(chooser_loc,55);
        arduboy.print(F("\x1E"));
        arduboy.display();
        arduboy.pollButtons();
            if (arduboy.justPressed(LEFT_BUTTON)){
                if (chooser>1){
                    arduboy.setCursor(chooser_loc,55);
                    arduboy.print(F(" "));
                    chooser--;}
            }
            if (arduboy.justPressed(RIGHT_BUTTON)){
                if (chooser<3){
                    arduboy.setCursor(chooser_loc,55);
                    arduboy.print(F(" "));
                    chooser++;}
            }
    } while (!arduboy.justPressed(A_BUTTON));

    //reveal the lion!
    for (int8_t i=0;i<50;i+=10){  
        if (i==30){
            arduboy.setCursor(door_pos,20);
            arduboy.print(F("LION"));
        }
        arduboy.drawBitmap(10,i,door,25,10,BLACK);
        arduboy.drawBitmap(50,i,door,25,10,BLACK);
        arduboy.drawBitmap(90,i,door,25,10,BLACK);
        arduboy.display();
        delay(250);   
    }
    delay(1000);

    if (chooser==rnd_door){
        lose_text("\n\nEATEN!!");
        return lose;
    }
    win_text("\n\nEscaped!");
    return win;
    
}
int8_t surrounded(Baddies baddy_type){
    String space = "\x00";
    String player_icon = "\x03";
    String baddy_name="Blabbers";
    String baddy="\xF9"; //Blabbers

    if(baddy_type == Baddies::Najjers){
        baddy = "\x23";
        baddy_name="Najjers";
    }

    arduboy.clear();
    arduboy.print(F("Surrounded by "));arduboy.print(baddy_name);
    arduboy.print(F("\npress correct 3"));
    arduboy.print(F("\nout of 4 direction"));
    arduboy.print(F("\npads to vanquish!"));
    arduboy.display();
    delay(3000);
    //starting positions of baddies
    int8_t C1x=6,C1y=1,C2x=64,C2y=1,C3x=117,C3y=1,C4x=6,C4y=32,C5x=117,C5y=32,C6x=6,C6y=54,C7x=64,C7y=54,C8x=117,C8y=54;
    //starting baddy sprite
    String D1=baddy,D2=baddy,D3=baddy;
    //set the random keys needed to be pressed
    arduboy.initRandomSeed();
    int8_t E1=random(1, 5),E2=random(1, 5),E3=random(1, 5);

    //now you have 3 chances to get it right:
    for (int i=1;i<4;i++){
        //font is 5x8
        arduboy.clear();
        arduboy.setCursor(Arduboy2::width()/2,Arduboy2::height()/2);
        arduboy.print(player_icon);
        //print baddies
        arduboy.setCursor(C1x,C1y); arduboy.print(D1); //top left
        arduboy.setCursor(C2x,C2y); arduboy.print(D2); //middle
        arduboy.setCursor(C3x,C3y); arduboy.print(D3); //top right
        //next row
        arduboy.setCursor(C4x,C4y); arduboy.print(D1); //top left
        arduboy.setCursor(C5x,C5y); arduboy.print(D2); //top right
        //next row
        arduboy.setCursor(C6x,C6y); arduboy.print(D3); //top left
        arduboy.setCursor(C7x,C7y); arduboy.print(D2); //middle
        arduboy.setCursor(C8x,C8y); arduboy.print(D1); //top right
        arduboy.display();

        

        //arduboy.waitNoButtons();
        bool btnPress=false;
        int8_t keyPressed=0;
        do{
            arduboy.pollButtons();
            if (arduboy.justPressed(UP_BUTTON)){keyPressed=1;btnPress=true;}
            else if (arduboy.justPressed(DOWN_BUTTON)){keyPressed=2;btnPress=true;}
            else if (arduboy.justPressed(LEFT_BUTTON)){keyPressed=3;btnPress=true;}
            else if (arduboy.justPressed(RIGHT_BUTTON)){keyPressed=4;btnPress=true;}
            if (keyPressed==E1 && btnPress){D1=space;}
            if (keyPressed==E2 && btnPress){D2=space;}
            if (keyPressed==E3 && btnPress){D3=space;}
        }while (!btnPress);
        //move the monsters in on the player
        C1x+=6,C1y+=8,C2y+=8,C3x-=6,C3y+=8,C4x+=6,C5x-=6,C6x+=6,C6y-=8,C7y-=8,C8x-=6,C8y-=8;

        if (D1==space && D2==space && D3==space){
                delay(1000);
                win_text("\n\nLUCKY!");
                return win;
            }
        
    }
    lose_text("\n\nSCROMP!!");
    return lose;
}
int8_t gambler(){
    //The Gruesome Gambler
    arduboy.clear();
    arduboy.print(F("The Gruesome Gambler!"));
    arduboy.print(F("\nthrow a higher or"));
    arduboy.print(F("\nlower dice, than"));
    arduboy.print(F("\nthe Gambler!"));
    arduboy.print("\nmore   \x1F");
    //arduboy.print("\n\x1F"); //down arrow
    arduboy.display();
    wait_for_key_press(DOWN_BUTTON);
    arduboy.clear();
    arduboy.print(F("but, he won't say"));
    arduboy.print(F("\nwhich way will win"));
    arduboy.print(F("\nuntil after you roll!"));
    arduboy.print(F("\nPress A to Start"));
    arduboy.display();
    wait_for_key_press(A_BUTTON);
    //player's roll
    arduboy.clear();
    arduboy.print(F("Press A to roll"));
    arduboy.display();
    wait_for_key_press(A_BUTTON);
    int player_dice_one = dice_roll(20, 32);
    int player_dice_two = dice_roll(80, 32);
    int player_total = player_dice_one+player_dice_two;
    arduboy.setCursor(0, 0);
    arduboy.print(F("\nYou scored "));
    arduboy.print(player_total);
    arduboy.display();
    delay(3000);
    //Gamler's turn
    arduboy.clear();
    arduboy.print(F("Gambler's turn!"));
    arduboy.display();
    delay(1000);
    int gambler_dice_one = dice_roll(20, 32);
    int gambler_dice_two = dice_roll(80, 32);
    int gambler_total = gambler_dice_one+gambler_dice_two;
    arduboy.setCursor(0, 0);
    arduboy.print(F("Gambler scored "));
    arduboy.print(gambler_total);
    arduboy.display();
    delay(3000);
    //decide if win or lose!
    arduboy.clear();
    arduboy.print(F("Gambler bet he"));
    arduboy.print(F("\nwould score..."));
    arduboy.display();
    delay(2000);
    arduboy.initRandomSeed();
    int8_t rnd_outcome = random(1, 3);
    if (rnd_outcome==1){
        arduboy.print(F("\nMORE!!!"));
        delay(500);
        if(gambler_total>player_total){
            arduboy.print(F("\n\nYOU LOSE!"));
            arduboy.display();
            delay(3000);
            return lose;
        }
        else{
            arduboy.print(F("\n\nYOU WIN!"));
            arduboy.display();
            delay(3000);
            return win;
        }
    }
    else {
        arduboy.print(F("\nLESS!!!"));
        delay(500);
        if(gambler_total<player_total){
            arduboy.print(F("\n\nYOU LOSE!"));
            arduboy.display();
            delay(3000);
            return lose;
        }
        else{
            arduboy.print(F("\n\nYOU WIN!"));
            arduboy.display();
            delay(3000);
            return win;
        }
    }
}
int8_t backtostart(){
    arduboy.clear();
    arduboy.print(F("\nBack to the Start!"));
    arduboy.display();
    delay(3000);
    player_x = 10; player_y = 30; //:: used to access external global vars
    return win;
}
