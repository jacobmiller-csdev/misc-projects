#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Designates LCD display formatting + address
LiquidCrystal_I2C lcd(0x27,20,4);

//Initializes LCD displays, serial monitor, and voltage output pins
void setup() {

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();  
  
  //Sets pins 2, 3, and 4 as a 5V voltage output
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);

  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  //Flag for designating which voltage is active
  

  //test code for disabling voltage outputs
  //and consequently the potentiometers using them
  //digitalWrite(2, LOW);

  //For testing purposes I may hard-code voltage values temporarily
  
}

//Flag for designating which voltage is active
//Global variable in order to avoid repeatedly overwriting back to 0 by declaring in main loop
int voltageFlag = 0;

void loop() {

  //Serial.println((String)"Other Test");
  
  //Refresh LCD Displays
  lcd.init();
  lcd.backlight(); 
  
  //Raw values provided by each potentiometer
  int XYValue = analogRead(A0);
  int XZValue = analogRead(A1);
  int YZValue = analogRead(A2);

  //Adjusted values to properly indicate voltage
  float XYVoltage = XYValue * (5.0/1023.0);
  float XZVoltage = XZValue * (5.0/1023.0);
  float YZVoltage = YZValue * (5.0/1023.0);
  //float test_voltage = XZValue *  (5.0/1023.0);

/*
 * Outdated method for preventing multiple voltages from being active at the same time.
 * In their current state, the conditions below this commented portion of the program only allow
 * the highest voltage to be actively sent to the coil and displays.
 * 
  //Condition to disable voltages upon detecting more than one potentiometer being active at once
  //Note: this just checks for any 2 voltages to be active at the same time then shuts down all 3
  //Can be altered to accomplish a more specific effect (i.e. disabling specific voltages instead of all of them
  if (((XYVoltage > 0.05) && (XZVoltage > 0.05)) 
     || ((XYVoltage > 0.05) && (YZVoltage > 0.05))
     || ((YZVoltage > 0.05) && (XZVoltage > 0.05))){

      //digitalWrite(2, LOW);
      Serial.println((String)"Detected multiple voltages active at once, all voltages disabled.");
      voltageFlag = 0;

      //Should I sleep here briefly to give system time to reset
      //Or some kind of other placeholder for what will happen with this
  
  }

  //Go here if no voltage conflicts, prints whichever voltage is active
  //If there is a change in which voltage is active, prints message denoting that change
  //Will likely be slightly more complicated for final implementation
  else{
*/
    //if XY voltage is highest
    if(XYVoltage > XZVoltage && XYVoltage > YZVoltage){
      
      //Sets active voltage to XY voltage if it isn't already
      if(voltageFlag != 1){
        //Serial.println((String)"Active voltage is now XY voltage.");
        voltageFlag = 1;
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
        digitalWrite(4, HIGH);
        delay(500);
      }

      //Displays XY Voltage on serial monitor and LCD displays
      Serial.println((String)"XY Voltage: " + XYVoltage);
      //Serial.println((String)"TEST: " + test_voltage);
      lcd.setCursor(0,0);
      lcd.print(XYVoltage);
    }

    //if XZ voltage is highest
    if(XZVoltage > XYVoltage && XZVoltage > YZVoltage){
      
      //Sets active voltage to XZ voltage if it isn't already
      if(voltageFlag != 2){
        //Serial.println((String)"Active voltage is now XZ voltage.");
        voltageFlag = 2;
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        delay(500);
      }

      //Displays XZ Voltage on serial monitor and LCD displays
      Serial.println((String)"XZ Voltage: " + XZVoltage);
      lcd.setCursor(0,0);
      lcd.print(XZVoltage);
    }

    //if YZ voltage is highest
    if(YZVoltage > XYVoltage && YZVoltage > XZVoltage){
      
      //Sets active voltage to YZ voltage if it isn't already
      if(voltageFlag != 3){
        //Serial.println((String)"Active voltage is now YZ voltage.");
        voltageFlag = 3;
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
        delay(500);
      }
      
      //Displays YZ Voltage on serial monitor and LCD displays
      Serial.println((String)"YZ Voltage: " + YZVoltage);
      lcd.setCursor(0,0);
      lcd.print(YZVoltage);
    }
    //Serial.println((String)"Test");
    
  //}
  
}
