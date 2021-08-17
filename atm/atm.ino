#include <Keypad.h>
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
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
int atm(){
  char pass[] = {'1','2','3','4'};
  char passin[4],i,t=0;
  Serial.print("Enter Pin: ");
  for(i=0;i<4;i++){
    char customKey = customKeypad.getKey();
    //if(customKey){
      //passin[i] = Serial.read();
      Serial.print(customKey);
      if(customKey != pass[i]){
      Serial.println("Wrong Password");
      return 123;
      }
      else t++;
    //}
  }
  /*for(i=0;i<4;i++){
    if(passin[i] != pass[i]){
      Serial.println("Wrong Password");
      return 123;
    }*/
    if(t==4){
      Serial.println("1 Avail Bal");
      Serial.println("2 Withdraw");
      Serial.println("3 Emergency");
    }
  
}



void setup() {
  Serial.begin(9600);
  atm();
}

void loop() {
  // put your main code here, to run repeatedly:
  //atm();
}
