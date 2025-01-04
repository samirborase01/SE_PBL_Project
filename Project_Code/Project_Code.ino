#include <LiquidCrystal.h>
#define RS                    PIN_PB0
#define RW                    PIN_PD7
#define D4                    PIN_PD6
#define D5                    PIN_PD5
#define D6                    PIN_PB7
#define D7                    PIN_PB6
#define Relay                 PIN_PD2
LiquidCrystal lcd(RS, RW, D4, D5, D6, D7);
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
                             {'1','4','7','A'},
                             {'2','5','8','B'},
                             {'3','6','9','C'},
                             {'*','0','#','D'}
                                              };
byte rowPins[ROWS] = {PIN_PB4, PIN_PC0, PIN_PC3, PIN_PC5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {PIN_PB1, PIN_PB2, PIN_PB3, PIN_PB5}; //connect to the column pinouts of the keypad

//byte rowPins[ROWS] = {PIN_PC5, PIN_PC3, PIN_PC0, PIN_PB4}; //connect to the row pinouts of the keypad
//byte colPins[COLS] = {PIN_PB1, PIN_PB2, PIN_PB3, PIN_PB5}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

char password[] = "2024"; // Set your password here
char enteredPassword[5]; // Buffer to store entered password
int passwordIndex = 0; // Index to keep track of entered password
String message = String("Password Base Circuit Breaker ATmega328P");
int length; 

void setup() 
{
  lcd.begin(16,2);
  lcd.setCursor(0, 0);
  lcd.print("Project Name:-  ");
  length = message.length();
  for(int i = 0; i < length; i++)
  {
    ClearRow(1);
    lcd.print(message.substring(i,i+15));
    delay(1000);
  }
  //Serial.begin(9600);
  pinMode(Relay, OUTPUT);
}

void loop() 
{
  char key = customKeypad.getKey();
  if (key != '\0') 
  {
    if (key == '#') 
    {
      // Check the entered password when # is pressed
      enteredPassword[passwordIndex] = '\0'; // Null terminate the entered password
      if (strcmp(enteredPassword, password) == 0) 
      {
        lcd.clear();
        lcd.print("Access Granted");
        digitalWrite(Relay, HIGH);
      } 
      else 
      {
        lcd.clear();
        lcd.print("Wrong Password");
        delay(1000);
        lcd.clear();
        lcd.print("Enter Password:");
        digitalWrite(Relay, LOW);
      }
      passwordIndex = 0; // Reset password index
    } 
    else 
    {
      enteredPassword[passwordIndex++] = key; // Store entered character in password buffer
      lcd.setCursor(passwordIndex - 1, 1);
      lcd.print(''); // Display '' for each entered character
    }
  }
}

void ClearRow(int rowNum)
{
  lcd.setCursor(0,rowNum);
  lcd.print("                 ");
  lcd.setCursor(0,rowNum);
}
