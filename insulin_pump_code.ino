// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.

// Modified for SPFD5408 Library by Joao Lopes
// Version 0.9.2 - Rotation for Mega and screen initial

// *** SPFD5408 change -- Begin
#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>
#include <Stepper.h>
// *** SPFD5408 change -- End

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#define pot A8


int sensorvalue;
int inputdata = 0;
int currentpage;
const int steppin = 38;
const int dirpin = 36;

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// Assign human-readable names to some common 16-bit color values:


bool backsensed = false;
bool resetsensed = false;
bool scrPress = false;  //Store weather sensed some touch and store


Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;

unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(BLACK);
  tft.fillScreen(RED);
  tft.fillScreen(GREEN);
  tft.fillScreen(BLUE);
  tft.fillScreen(BLACK);
  return micros() - start;
}

unsigned long testText() {
  tft.setRotation(1);
  tft.fillScreen(RED);
  unsigned long start = micros();
  tft.setCursor(70, 10);
  tft.setTextSize(2);
  tft.println(" Insulin Pump ");
  tft.setCursor(50, 70);
  tft.setTextSize(2);
  tft.println("BG Level ");
  tft.drawRoundRect(160, 50, 90, 50, 6, WHITE );
  tft.setCursor(15, 140);
  tft.setTextSize(2);
  tft.println("Active:Bolus");
  tft.setCursor(190, 140);
  tft.setTextSize(2);
  tft.println("UNIT:1.5");
  tft.setCursor(15, 170);
  tft.setTextSize(2);
  tft.println("Activate");
  tft.setCursor(200, 170);
  tft.setTextSize(2);
  tft.println("Settings");

  return micros() - start;
}

unsigned long testText1() {
  tft.setRotation(1);
  tft.fillScreen(RED);
  unsigned long start = micros();
  tft.setCursor(70, 10);
  tft.setTextSize(2);
  tft.println(" Insulin Pump ");
  tft.setCursor(50, 70);
  tft.setTextSize(2);
  tft.println("BG Level ");
  tft.drawRoundRect(160, 50, 90, 50, 6, WHITE );
  tft.setCursor(15, 140);
  tft.setTextSize(2);
  tft.println("Active:Balas");
  tft.setCursor(190, 140);
  tft.setTextSize(2);
  tft.println("UNIT:1.0");
  tft.setCursor(15, 170);
  tft.setTextSize(2);
  tft.println("Activate");
  tft.setCursor(200, 170);
  tft.setTextSize(2);
  tft.println("Settings");

  return micros() - start;
}
unsigned long testText3() {
  tft.setRotation(1);
  tft.fillScreen(RED);
  unsigned long start = micros();
  tft.setCursor(70, 10);
  tft.setTextSize(2);
  tft.println(" Settings Menu");
  tft.setCursor(50, 70);
  tft.setTextSize(2);
  tft.println("1.Bolus Setting");
  tft.setCursor(50, 95);
  tft.setTextSize(2);
  tft.println("2.Basal Setting");
  tft.setCursor(50, 120);
  tft.setTextSize(2);
  tft.println("3.Device Setting");
  tft.setCursor(50, 145);
  tft.setTextSize(2);
  tft.println("4.Active Unit");
  tft.setCursor(50, 170);
  tft.setTextSize(2);
  tft.println("5.Save & Exit");

  return micros() - start;
}
unsigned long testText4() {
  tft.setRotation(1);
  tft.fillScreen(RED);
  unsigned long start = micros();
  tft.setCursor(70, 10);
  tft.setTextSize(2);
  tft.println(" Hypoglycemia");
  tft.setCursor(50, 70);
  tft.setTextSize(2);
  tft.println("BG Level = 60 mg/dl");
  //tft.drawRoundRect(160, 50, 90, 50, 6, WHITE );
  tft.setCursor(15, 140);
  tft.setTextSize(2);
  tft.println("Active:Bolus");
  tft.setCursor(190, 140);
  tft.setTextSize(2);
  tft.println("UNIT:1.0");
  tft.setCursor(15, 170);
  return micros() - start;
}
unsigned long testText5() {
  tft.setRotation(1);
  tft.fillScreen(RED);
  unsigned long start = micros();
  tft.setCursor(70, 10);
  tft.setTextSize(2);
  tft.println(" Normal Operation");
  tft.setCursor(50, 70);
  tft.setTextSize(2);
  tft.println("BG Level = 180 mg/dl");
  //tft.drawRoundRect(160, 50, 90, 50, 6, WHITE );
  tft.setCursor(15, 140);
  tft.setTextSize(2);
  tft.println("Active:Bolus");
  tft.setCursor(190, 140);
  tft.setTextSize(2);
  tft.println("UNIT:1.0");
  tft.setCursor(15, 170);
  return micros() - start;
}
unsigned long testText6() {
  tft.setRotation(1);
  tft.fillScreen(RED);
  unsigned long start = micros();
  tft.setCursor(70, 10);
  tft.setTextSize(2);
  tft.println(" Hyperglycemia");
  tft.setCursor(50, 70);
  tft.setTextSize(2);
  tft.println("BG Level = 255 mg/dl");
  //tft.drawRoundRect(160, 50, 90, 50, 6, WHITE );
  tft.setCursor(15, 140);
  tft.setTextSize(2);
  tft.println("Active:Bolus");
  tft.setCursor(190, 140);
  tft.setTextSize(2);
  tft.println("UNIT:1.0");
  tft.setCursor(15, 170);
  return micros() - start;
}
unsigned long testText7() {
  tft.setRotation(1);
  tft.fillScreen(RED);
  unsigned long start = micros();
  tft.setCursor(70, 10);
  tft.setTextSize(2);
  tft.println(" Insulin injected");

  return micros() - start;
}
unsigned long testText8() {
  tft.setRotation(1);
  tft.fillScreen(RED);
  unsigned long start = micros();
  tft.setCursor(70, 10);
  tft.setTextSize(2);
  tft.println(" Injection done");

  return micros() - start;
}


void setup(void) {

  pinMode(26, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(30, OUTPUT);
  // pinMode(A8, INPUT);
  pinMode(42, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(50, OUTPUT);
  Serial1.begin(9600);

  // Code changed to works

  tft.begin(0x9341); // SDFP5408

  tft.setRotation(1); // Need for the Mega, please changed for your choice or rotation initial

  tft.fillScreen(BLACK);
  drawHome();
  //delay(5000);
}

void drawHome()
{

  tft.fillScreen(BLACK);
  tft.drawRoundRect(0, 0, 319, 240, 8, WHITE);     //Page border

  tft.fillRoundRect(60, 180, 200, 40, 8, RED);
  tft.drawRoundRect(60, 180, 200, 40, 8, WHITE);  //Settings Menu

  tft.fillRoundRect(60, 130, 200, 40, 8, RED);   //Activate Menu
  tft.drawRoundRect(60, 130, 200, 40, 8, WHITE);

  tft.fillRoundRect(60, 80, 200, 40, 8, RED);
  tft.drawRoundRect(60, 80, 200, 40, 8, WHITE); //Bg Level

  tft.setCursor(60, 20);
  tft.setTextSize(2);
  //tft.setFont();
  tft.setTextColor(WHITE);
  tft.print("Select an option");
  tft.setCursor(70, 50);
  tft.setTextSize(2);
  tft.setTextColor(LIME);
  tft.print("Insulin Pump");
  tft.setTextColor(BLACK);
  tft.setCursor(60, 195);
  tft.print("Settings Menu");

  tft.setCursor(90, 145);
  tft.print("Activate Menu");

  tft.setCursor(100, 95);
  tft.print("BG Level");
}

void loop(void) {

  //drawHome();
  //delay(500);
  //ActivateMenu();
  sensorvalue = analogRead(A8);
  buttonstate1 = digitalRead(42);
  buttonstate2 = digitalRead(44);
  buttonstate3 = digitalRead(46);
  

  if (buttonstate1 == HIGH)
  {
    testText();
    delay(5000);
    potvalue();
  }
  else if (buttonstate2 == HIGH)
  {
    SettingsMenu();
    //delay(5000);

  }
  else if (buttonstate3 == HIGH)
  {
    ActivateMenu();
    //delay(5000);

  }
  else if (buttonstate4 == HIGH)
  {
    drawHome();
    //delay(5000);
  }





}

void potvalue()
{

  
  if (sensorvalue < 340)
  {
    digitalWrite(26, HIGH);
    delay(1000);
    testText4();
    delay(1000);
    digitalWrite(26, LOW);
  }
  else if ((sensorvalue > 340) && (sensorvalue < 680))
  {
    digitalWrite(28, HIGH);
    delay(1000);

    testText5();
    delay(1000);
    digitalWrite(28, LOW);
  }
  else if ((sensorvalue > 680) && (sensorvalue < 1023))
  {
    digitalWrite(30, HIGH);
    delay(1000);

    testText6();
    delay(1000);
    while(Serial1.available())
    {
      
      if (Serial1.available() > 0)
      {
        inputdata = Serial1.read();        //Read the incoming data & store into data


        if (inputdata == 1) {
          digitalWrite(dirpin, HIGH);
          //delay(500);
            for (int x = 200; x >= 0; x--)
             {
            //  Serial.print("Insulin is being filled in syringe\n");
            digitalWrite(steppin, HIGH);
            delayMicroseconds(1000);
            digitalWrite(steppin, LOW);
            delayMicroseconds(1000);
          }
        }

        else if(inputdata==2)
        {
          digitalWrite(dirpin, LOW);
          for (int x = 0; x <= 200; x++)

          {
            //Serial.print("Insulin is being injected in patient's blood\n");
            digitalWrite(steppin, HIGH);
            delayMicroseconds(1000);
            digitalWrite(steppin, LOW);
            delayMicroseconds(1000);
          }
        }
      }
      /*else {
        testText3();*/
      }
     // digitalWrite(30, LOW);
    
  }
}




  void SettingsMenu()
  {
    tft.fillScreen(BLACK);
    tft.drawRoundRect(0, 0, 319, 240, 8, WHITE);     //Page border

    tft.fillRoundRect(60, 180, 200, 40, 8, RED);
    tft.drawRoundRect(60, 180, 200, 40, 8, WHITE);  //Settings Menu

    tft.fillRoundRect(60, 130, 200, 40, 8, RED);   //Activate Menu
    tft.drawRoundRect(60, 130, 200, 40, 8, WHITE);

    tft.fillRoundRect(60, 80, 200, 40, 8, RED);
    tft.drawRoundRect(60, 80, 200, 40, 8, WHITE); //Bg Level

    tft.setCursor(60, 20);
    tft.setTextSize(2);
    //tft.setFont();
    tft.setTextColor(WHITE);
    tft.print("Select an option");
    tft.setCursor(70, 50);
    tft.setTextSize(2);
    tft.setTextColor(LIME);
    tft.print("Settings Menu");
    tft.setTextColor(BLACK);
    tft.setCursor(80, 195);
    tft.print("Basal Setting");

    tft.setCursor(80, 145);
    tft.print("Bolus Setting");

    tft.setCursor(80, 95);
    tft.print("Device Setting");
  }

  void ActivateMenu()
  {
    tft.fillScreen(BLACK);
    tft.drawRoundRect(0, 0, 319, 240, 8, WHITE);     //Page border

    tft.fillRoundRect(60, 180, 200, 40, 8, RED);
    tft.drawRoundRect(60, 180, 200, 40, 8, WHITE);  //Settings Menu

    tft.fillRoundRect(60, 130, 200, 40, 8, RED);   //Activate Menu
    tft.drawRoundRect(60, 130, 200, 40, 8, WHITE);

    tft.fillRoundRect(60, 80, 200, 40, 8, RED);
    tft.drawRoundRect(60, 80, 200, 40, 8, WHITE); //Bg Level

    tft.setCursor(60, 20);
    tft.setTextSize(2);
    //tft.setFont();
    tft.setTextColor(WHITE);
    tft.print("Select an option");
    tft.setCursor(65, 50);
    tft.setTextSize(2);
    tft.setTextColor(LIME);
    tft.print("Activate Menu");
    tft.setTextColor(BLACK);
    tft.setCursor(70, 195);
    tft.print(" Save & Exit ");

    tft.setCursor(65, 145);
    tft.print(" Activate Bolus ");

    tft.setCursor(80, 95);
    tft.print("Activate  Basal");
  }
