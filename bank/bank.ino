#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int i,in[4];
int keypad(){
  digitalWrite(22, LOW);
  for(i=23;i<26;i++)
    digitalWrite(i, HIGH);
  for(i=26;i<30;i++)
    in[i-26] = digitalRead(i);
  if(in[0]==0 && in[1]==1 && in[2]==1 && in[3]==1)
    return 1;
  else if(in[0]==1 && in[1]==0 && in[2]==1 && in[3]==1)
    return 2;
  else if(in[0]==1 && in[1]==1 && in[2]==0 && in[3]==1)
    return 3;
  else if(in[0]==1 && in[1]==1 && in[2]==1 && in[3]==0)
    return 4;

  digitalWrite(22, HIGH);
  digitalWrite(23, LOW);
  digitalWrite(24, HIGH);
  digitalWrite(25, HIGH);
  for(i=26;i<30;i++)
    in[i-26] = digitalRead(i);
  if(in[0]==0 && in[1]==1 && in[2]==1 && in[3]==1)
    return 5;
  else if(in[0]==1 && in[1]==0 && in[2]==1 && in[3]==1)
    return 6;
  else if(in[0]==1 && in[1]==1 && in[2]==0 && in[3]==1)
    return 7;
  else if(in[0]==1 && in[1]==1 && in[2]==1 && in[3]==0)
    return 8;


  digitalWrite(22, HIGH);
  digitalWrite(23, HIGH);
  digitalWrite(24, LOW);
  digitalWrite(25, HIGH);
  for(i=26;i<30;i++)
    in[i-26] = digitalRead(i);
  if(in[0]==0 && in[1]==1 && in[2]==1 && in[3]==1)
    return 9;
  else if(in[0]==1 && in[1]==0 && in[2]==1 && in[3]==1)
    return 10;
  else if(in[0]==1 && in[1]==1 && in[2]==0 && in[3]==1)
    return 11;
  else if(in[0]==1 && in[1]==1 && in[2]==1 && in[3]==0)
    return 12;

  digitalWrite(22, HIGH);
  digitalWrite(23, HIGH);
  digitalWrite(24, HIGH);
  digitalWrite(25, LOW);
  for(i=26;i<30;i++)
    in[i-26] = digitalRead(i);
  if(in[0]==0 && in[1]==1 && in[2]==1 && in[3]==1)
    return 13;
  else if(in[0]==1 && in[1]==0 && in[2]==1 && in[3]==1)
    return 14;
  else if(in[0]==1 && in[1]==1 && in[2]==0 && in[3]==1)
    return 15;
  else if(in[0]==1 && in[1]==1 && in[2]==1 && in[3]==0)
    return 16;
}


void setup() {
  // Keypad
  for(i=22;i<26;i++)
    pinMode(i, OUTPUT);
  for(i=26;i<30;i++)
    pinMode(i, INPUT);

  //LCD
  lcd.begin(16,2);
  

}

void loop() {
  int k;
  k = keypad();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(k);
  delay(10);
}
