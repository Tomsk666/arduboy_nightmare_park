void win_text(String txtMsg){
  arduboy.clear();
  arduboy.print(txtMsg);
  arduboy.display();
  delay(2500);
}
void lose_text(String txtMsg){
  arduboy.clear();
  arduboy.print(txtMsg);
  arduboy.display();
  delay(2500);
}

void wait_for_key_press(uint8_t button){
    bool button_press=false;
    arduboy.waitNoButtons();
    do
    {
        if (arduboy.pressed(button))
        {
            button_press = true;
            return;
        }
    } while (!button_press);
}

void draw_dice(int8_t X, int8_t Y, int8_t die_num){
  switch (die_num)
  {
  case 1:
    Sprites::drawOverwrite(X,Y,Dice1, 0);
    //arduboy.drawBitmap(X,Y,Dice1,30,30,WHITE);
    break;
  case 2:
    Sprites::drawOverwrite(X,Y,Dice2, 0);
    //arduboy.drawBitmap(X,Y,Dice2,30,30,WHITE);
    break;
  case 3:
    Sprites::drawOverwrite(X,Y,Dice3, 0);
    //arduboy.drawBitmap(X,Y,Dice3,30,30,WHITE);
    break;
  case 4:
    Sprites::drawOverwrite(X,Y,Dice4, 0);
    //arduboy.drawBitmap(X,Y,Dice4,30,30,WHITE);
    break;
  case 5:
    Sprites::drawOverwrite(X,Y,Dice5, 0);
    //arduboy.drawBitmap(X,Y,Dice5,30,30,WHITE);
    break;
  case 6:
    Sprites::drawOverwrite(X,Y,Dice6, 0);
    //arduboy.drawBitmap(X,Y,Dice6,30,30,WHITE);
    break;
  }
}
int dice_roll(int8_t X, int8_t Y)
{
    int8_t dice_val;
    arduboy.initRandomSeed();
    for (int8_t i = 1; i <= 12; i++)
    {
        //arduboy.clear();
        dice_val = random(1, 7);
        draw_dice(X, Y, dice_val);
        arduboy.display();
        delay(i * 10 + 50);
    }
    return (dice_val);
}