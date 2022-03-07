#include <Wire.h> 
#include "HX711.h"
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
SoftwareSerial MyPhone(6, 7); //RX | TX 
HX711 scale;
#define LOADCELL_DOUT_PIN  4
#define LOADCELL_SCK_PIN  5

//bluetooth stuff
String start = "";
char c;

//button stuff
int button_switch1 = 2;
int button_switch2 = 3;
int led_switch = 13;
bool led_status = LOW;
volatile bool button_status1 = true;

//unit stuff
unsigned int unit;
char calibration_done = '\0';
float calibration_factor = -390;

void conversion()
{
  button_status1 = !button_status1;
}

void reset()
{
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare();
}

void setup() {

  Serial.begin(9600); // Interfata serial pentru PC
  MyPhone.begin(9600); // Interfata serial pentru Bluetooth
  
  //setup-ul pentru afisajul pe LCD
  lcd.init();                  
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Digital Weight");
  lcd.setCursor(1,1);
  lcd.print("Measuring 1.0");

  pinMode(led_switch, OUTPUT);
  pinMode(button_switch1, INPUT);
  pinMode(button_switch2, INPUT);
  digitalWrite(button_switch1, HIGH);
  digitalWrite(button_switch2, HIGH);
  digitalWrite(led_switch, led_status);
  attachInterrupt(digitalPinToInterrupt(button_switch1), conversion, FALLING);
  attachInterrupt(digitalPinToInterrupt(button_switch2), reset, FALLING);
  
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");
  Serial.println("Press s to complete the calibration");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);  //initializeaza biblioteca cu pinul de ieșire a datelor (DOUT) si pinul de intrare al ceasului (SCK)
  scale.set_scale(); //setarea valorii de scalare; aceasta valoare este utilizata pentru a converti datele brute in date „lizibile” (unitati de masura)
  scale.tare(); //se aduce valoarea de scalare la 0 (initializarea cantarului)
 
}

void calibration()
{
    scale.set_scale(calibration_factor); //se seteaza valoarea de scalare in functie de factorii externi(se foloseste un factor de calibrare pentru acest lucru)
    
    if(scale.get_units() >= 0){
      unit = scale.get_units();   //valoarea bruta impartita la o valoare obtinuta prin calibrare
    }  
    else{
       unit = 0;
    }   
    Serial.print("Reading: ");
    Serial.print(unit, 1);
    Serial.print(" grams"); 
    Serial.print(" calibration_factor: ");
    Serial.print(calibration_factor);
    Serial.println();
  
    if(Serial.available())
    {
      char temp = Serial.read();
      if(temp == '+' || temp == 'a')
        calibration_factor += 10;
      else 
        if(temp == '-' || temp == 'z')
          calibration_factor -= 10;
        else
          if(temp == 's')
            calibration_done = temp;   
    }
}

void loop() {

  while(MyPhone.available())
  {
    c = MyPhone.read();
    start.concat(c);
    delay(50);
  }
  if(start.length() > 0){
    start.setCharAt(start.length() - 2, '\0');  //ca sa eliminam caracterele netiparibile ce apar in transmiterea datelor
  }
  delay(50);
  
  if(start == "Start")
  {
      calibration();
      if(calibration_done == 's')
      {
           
           lcd.setCursor(0,0);
           lcd.print("Real time weight");
           if(button_status1)
           {
                lcd.setCursor(1,1);
                if(unit < 10)
                {
                  lcd.print("       ");
                  lcd.setCursor(8,1);
                  lcd.print(unit);  
                }
                else
                {
                    if(unit >= 10 && unit < 100)
                    {
                        lcd.print("      ");
                        lcd.setCursor(7,1);
                        lcd.print(unit);  
                    }
                    else
                    {
                        if(unit >= 100 && unit < 1000)
                        {
                            lcd.print("     ");
                            lcd.setCursor(6,1);
                            lcd.print(unit);  
                        }
                        else
                        {
                            lcd.print("    ");
                            lcd.setCursor(5,1);
                            lcd.print(unit);  
                        }
                    }
                }
                
                lcd.setCursor(9,1);
                lcd.print("g      ");
                
           }
           else
           {
                double kg_unit;
                kg_unit = ((double)unit) / 1000.0;
                lcd.print("   ");
                lcd.setCursor(4,1);
                lcd.print(kg_unit, 3);
                lcd.setCursor(9,1);
                lcd.print("kg     ");
           }

           if(unit > 2000){
               MyPhone.write("Over 2kg on here\n");
           }
           
           
           delay(500);
      }
      else
      {
          lcd.setCursor(1,0);
          lcd.print(" Waiting for  ");
          lcd.setCursor(1,1);
          lcd.print("calibration...");
      }
      
  }
  else{
    start = "";
  }
  
  
}

 
