#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Servo servo1,servo2,servo5,servoin,servoout;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'}
};
byte rowPins[ROWS] = {25, 24, 23, 22}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {29, 28, 27, 26}; //connect to the column pinouts of the keypad
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

char pass[4] = {'1','2','3','0'};char passin[4];
int amount,c1=0,c2=0,c5=0;
int i=0,t=0,j,a=0,b=0;
//int s1p=0,s2p=0,s5p=0;
int EAmount=0,WAmount=0,DAmount=0,Amount=0,Limit=8;
int s1,s2,s5,c1s=0,c2s=0,c5s=0,limit=0;
int TraM[10],tra=0;
char TraT[10]={'N','N','N','N','N','N','N','N','N','N'};
int c1c=0,c2c=0,c5c=0;

void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);
  servo1.attach(8);
  servo2.attach(9);
  servo5.attach(10);
  servoin.attach(6);
  servoout.attach(7);
  servo1.write(120);
  servo2.write(150);
  servo5.write(150);
  servoin.write(90);
  servoout.write(80);
  tra = 0;
  amount = c1 + 2 * c2 + 5 * c5;
  input :
  t=0;
  lcd.clear();
  lcd.print("Enter Pin");
  lcd.setCursor(0,1);
  for(i=0;i<4;){
  char customKey = customKeypad.getKey();
  if (customKey){
    Serial.println(customKey);
    lcd.print(customKey);
    passin[i] = customKey;
    i++;
  }
  }
  for(i=0;i<4;i++){
    if(passin[i] != pass[i]){
      Serial.print("Wrong Pin");
      lcd.clear();
      lcd.print("Wrong Pin!!!");
      //return;
      delay(1000);
      goto input;
    }
    else{
      t++;
    }
  }
  Serial.println(t);
  if(t==4){
      options :
      lcd.setCursor(0,0);
      lcd.print("1 Deposit Money");
      lcd.setCursor(0,1);
      lcd.print("2 Avail Balance");
      for(i=0;i<1;){
        char customKey = customKeypad.getKey();
        if (customKey){
          Serial.println(customKey);
          
          
          //Deposit Money Start
          if(customKey == '1')
          {
            Deposit :
            lcd.clear();
            lcd.print("Enter Coins,if");
            lcd.setCursor(0,1);
            lcd.print("Done press Enter");
            servoin.write(150);
            delay(1000);
            Amount = 0;
            s1=0;s2=0;s5=0;
            for(i=0;;)
            {
              customKey = customKeypad.getKey();
              if (customKey)
              {
                if(customKey == 'F')
                {
                  TraM[tra] = Amount;
                  TraT[tra] = 'D';
                  tra++;
                  amount = c1 + 2 * c2 + 5 * c5;
                  Amount = s1 + 2 * s2 + 5 * s5;
                  c1+=s1;c2+=s2;c5+=s5;
                  amount += Amount;
                  lcd.clear();
                  lcd.print(Amount);
                  lcd.print(" Added");
                  lcd.setCursor(0,1);
                  lcd.print("Total Amount:");
                  lcd.print(amount);
                  servoin.write(90);
                  delay(500);
                  goto input;
                }
                else if(customKey == 'C' && Amount == 0)
                {
                  servoin.write(90);
                  delay(200);
                  goto options;
                }
                else if(customKey == 'D' && Amount == 0)
                {
                  servoin.write(90);
                  delay(200);
                  goto input;
                }
                else
                {
                  lcd.clear();
                  lcd.print("Press Enter");
                  lcd.setCursor(0,1);
                  lcd.print("When Done");
                  delay(1000);
                }
              }
              lcd.clear();
              lcd.print("Amount : ");
              if(digitalRead(50) == 1)
              {
                s1++;
                delay(100);
              }
              if(digitalRead(51) == 1)
              {
                s2++;
                delay(100);
              }
              if(digitalRead(52) == 1)
              {
                s5++;
                delay(100);
              }
              Amount = s1 + 2 * s2 + 5 * s5;
              lcd.setCursor(0,1);
              lcd.print(Amount);
            }
          }//Deposit Money End
          

          //Available Balance Strat
          else if(customKey == '2')
          { 
            lcd.clear();
            lcd.print("Avail Balance");
            amount = c1 + 2 * c2 + 5 * c5;
            lcd.setCursor(0,1);
            lcd.print(amount);
            delay(1000);
            goto options;
          }//Available Balance End


          // Withdraw Money Start
          else if(customKey == '3')
          {
            Withdraw :
            WAmount = 0;
            Amount = 0;
            lcd.clear();
            lcd.print("Enter Amount");
            lcd.setCursor(0,1);
            for(i=0;;)
            {
              customKey = customKeypad.getKey();
              if (customKey)
              {
                t = customKey - 48;
                if(t>=0 && t<=9)
                {
                  lcd.print(customKey);
                  if(i==0)
                  {
                    Amount = t*10;
                    i++;
                  }
                  else if(i==1)
                  {
                    Amount += t;
                    i++;
                  }
                }
                //Clear
                else if(customKey == 'B') 
                  goto Withdraw;
                else if(customKey == 'D') //Exit
                  goto input;
                else if(customKey == 'C') //Cancel
                  goto options;
                else if(customKey == 'F'){
                  Serial.println(Amount);
                  amount = c1 + 2 * c2 + 5 * c5;
                  if(Amount > amount)
                  {
                    lcd.clear();
                    lcd.print("Amount Exceed");
                    if((limit+Amount) > Limit)
                    {
                      lcd.setCursor(0,1);
                      lcd.print("Limit Exceed");
                    }
                    delay(1000);
                    goto Withdraw;
                  }
                  Serial.println(limit);
                  Serial.println(Limit);
                  if((limit+Amount) > Limit)
                  {
                    lcd.clear();
                    lcd.print("Limit Exceed");
                    lcd.setCursor(0,1);
                    lcd.print("Limit: ");
                    lcd.print(Limit);
                    delay(1000);
                    goto Withdraw;
                  }
                  //Withdraw
                  
                  if(Amount%2 == 1 && c1<1  && Amount < 5 || Amount == 1 && c1<1 || Amount == 4 && c2<2 || Amount == 2 && c2<1){
                        lcd.clear();
                        lcd.print("Invalid Amount");
                        delay(1000);
                        goto Withdraw;
                    }
                  if(Amount <= amount && (limit+Amount) <= Limit)
                  {
                    TraM[tra] = Amount;
                    TraT[tra] = 'W';
                    tra++;
                    limit = limit + Amount;
                    WAmount = Amount;
                    if(WAmount > 0)
                    {
                      while(WAmount >= 5 && c5 > 0)
                      {
                        /*
                          if(s5p == 0)
                          {
                            servo5.write();
                          }
                          else if(s5p == 1)
                          {
                            servo5.write(0);
                          }
                          */
                          servo5.write(60);
                          delay(500);
                          servo5.write(150);
                          delay(100);
                          c5--;
                          /*s5p++;
                          s5p %= 2;*/
                          WAmount -= 5;
                      }
                      while(WAmount >= 2 && c2 > 0)
                      {
                        /*if(s2p == 0)
                          servo2.write(180);
                        else if(s2p == 1)
                          servo2.write(0);*/
                        servo2.write(70);
                        delay(500);
                        servo2.write(150);
                        delay(100);
                        /*s2p++;
                        s2p %= 2;*/
                        c2--;
                        WAmount -= 2;
                      }
                      while(WAmount >= 1 && c1 > 0)
                      {
                        /*if(s1p == 0)
                          servo1.write(180);
                        else if(s1p == 1)
                          servo1.write(0);*/
                        servo1.write(30);
                        delay(500);
                        servo1.write(120);
                        delay(100);
                        c1--;
                        /*s1p++;
                        s1p %= 2;*/
                        WAmount -= 1;
                      }

                      servoout.write(0);
                      lcd.clear();
                      lcd.print("Collect It");
                      delay(10000);
                      servoout.write(80);
                      delay(100);
                      goto input;
                    }
                    //Serial.println(Amount); 
                  }
                }
              }
            }
          }// Withdraw Money End


          //Mini Statement Start
          else if(customKey == '4')
          {
            lcd.clear();
            lcd.print("Last 3 Transtion");
            lcd.setCursor(0,1);
            lcd.print(TraM[tra-1]);
            lcd.print(" : ");
            lcd.print(TraT[tra-1]);
            for(i=tra;;)
            {
              customKey = customKeypad.getKey();
              if (customKey)
              {
                if(customKey == 'E' && tra>1 )
                {
                  i = tra-2;
                  lcd.clear();
                  lcd.print(TraM[i]);
                  lcd.print(" : ");
                  lcd.print(TraT[i]);
                  lcd.setCursor(0,1);
                  i = tra-3;
                  lcd.print(TraM[i]);
                  lcd.print(" : ");
                  lcd.print(TraT[i]);
                }
                else if(customKey == 'A' && tra>0)
                {
                  lcd.clear();
                  lcd.print("Last 3 Transtion");
                  lcd.setCursor(0,1);
                  lcd.print(TraM[tra-1]);
                  lcd.print(" : ");
                  lcd.print(TraT[tra-1]);
                }
                else if(customKey == 'D') //Exit
                  goto input;
                else if(customKey == 'C' || customKey == 'B' || customKey == 'F') //Back to options
                  goto options;
              }
            }
          }//Mini Statement End



          //Emergency Start
          else if(customKey == '5')
          {
            Emergency :
            EAmount = 0;
            Amount = 0;
            lcd.clear();
            lcd.print("Enter Amount");
            lcd.setCursor(0,1);
            for(i=0;;)
            {
              customKey = customKeypad.getKey();
              if (customKey)
              {
                t = customKey - 48;
                if(t>=0 && t<=9)
                {
                  lcd.print(customKey);
                  if(i==0)
                  {
                    Amount = t*10;
                    i++;
                  }
                  else if(i==1)
                  {
                    Amount += t;
                    i++;
                  }
                }
                else if(customKey == 'B')
                  goto Emergency;
                else if(customKey == 'D')
                  goto input;
                else if(customKey == 'C')
                  goto options;
                else if(customKey == 'F')
                {
                  amount = c1 + 2 * c2 + 5 * c5;
                  if(Amount%2 == 1 && c1<1  && Amount < 5 || Amount == 1 && c1<1 || Amount == 4 && c2<2 || Amount == 2 && c2<1){
                        lcd.clear();
                        lcd.print("Invalid Amount");
                        delay(1000);
                        goto Emergency;
                  }
                  else if(Amount > amount)
                  {
                    lcd.clear();
                    lcd.print("Amount Exceed");
                    delay(1000);
                    goto Emergency;
                  }
                  else// if(Amount < amount)
                  {
                    TraM[tra] = Amount;
                    TraT[tra] = 'E';
                    tra++;
                    EAmount = Amount;
                    ///Withdraw  
                    while(EAmount >= 5 && c5 > 0)
                      {
                          /*if(s5p == 0)
                          {
                            servo5.write(180);
                          }
                          else if(s5p == 1)
                          {
                            servo5.write(0);
                          }*/
                          servo5.write(60);
                          delay(500);
                          servo5.write(150);
                          delay(100);
                          c5--;
                          /*s5p++;
                          s5p %= 2;*/
                          EAmount -= 5;
                      }
                      while(EAmount >= 2 && c2 > 0)
                      {
                        /*if(s2p == 0)
                          servo2.write(180);
                        else if(s2p == 1)
                          servo2.write(0);*/
                        servo2.write(70);
                        delay(500);
                        servo2.write(150);
                        delay(100);
                        c2--;
                        /*s2p++;
                        s2p %= 2;*/
                        EAmount -= 2;
                      }
                      while(EAmount >= 1 && c1 > 0)
                      {
                        /*if(s1p == 0)
                          servo1.write(180);
                        else if(s1p == 1)
                          servo1.write(0);*/
                        servo1.write(30);
                        delay(500);
                        servo1.write(120);
                        delay(100);
                        c1--;
                        /*s1p++;
                        s1p %= 2;*/
                        EAmount -= 1;
                      }
                      servoout.write(0);
                      lcd.clear();
                      lcd.print("Collect It");
                      delay(10000);
                      servoout.write(80);
                      delay(100);
                      goto input;
                  }
                   

                }
              }
            }
          }//Emergency End


          
          //PinChange Start
          else if(customKey == '6'){ 
              lcd.clear();
              lcd.print("Enter New Pin");
              lcd.setCursor(0,1);
              for(i=0;i<5;){
                customKey = customKeypad.getKey();
                if (customKey){
                  if(i==4){
                    if(customKey == 'B'){
                      lcd.clear();
                      lcd.print("Pin Not Set!!!");
                      delay(1000);
                      goto input;  
                    }
                    else if(customKey == 'F'){
                      lcd.clear();
                      lcd.print("Pin Set Sucess");
                      for(j=0;j<4;j++){
                        pass[j] = passin[j];
                      }
                      delay(1000);
                      goto input;
                    }
                    else{
                      lcd.setCursor(0,0);
                      lcd.print("Press Enter/Clr");
                    }
                  }
                  else if(i<4){
                    lcd.print(customKey);
                    passin[i] = customKey;
                    i++;
                  }
                }
              }
          }
          else if(customKey == 'E'){
            if(a==0){
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("2 Avail Money");
              lcd.setCursor(0,1);
              lcd.print("3 Withdraw Money");
              a++;
            }
            else if(a==1){
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("3 Withdraw Money");
              lcd.setCursor(0,1);
              lcd.print("4 Mini Statement");
              a++;
            }
            else if(a==2){
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("4 Mini Statement");
              lcd.setCursor(0,1);
              lcd.print("5 Emergency");
              a++;
            }
            else if(a==3){
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("5 Emergency");
              lcd.setCursor(0,1);
              lcd.print("6 Pin Change");
              a++;
            }
          }
          else if(customKey == 'A'){
            if(a==1){
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("1 Deposit Money");
              lcd.setCursor(0,1);
              lcd.print("2 Avail Balance");
              a--;
            }
            else if(a==2){
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("2 Avail Balance");
              lcd.setCursor(0,1);
              lcd.print("3 Withdraw Money");
              a--;
            }
            else if(a==3){
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("3 Withdraw Money");
              lcd.setCursor(0,1);
              lcd.print("4 Mini Statement");
              a--;
            }
            else if(a==4){
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("4 Mini Statement");
              lcd.setCursor(0,1);
              lcd.print("5 Emergency");
              a--;
            }
          }
          else if(customKey == 'D'){
            goto input;
          }
          else{
            lcd.clear();
            lcd.print("Wrong Input");
            delay(1000);
            goto options;          }
          
        }
      }
  }
}
  
void loop(){
  
  //ne();
}
