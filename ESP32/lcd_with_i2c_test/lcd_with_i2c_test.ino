//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                  
  lcd.backlight();

}


void loop()
{
  lcd.setCursor(2,0);
  lcd.print("Weather Pollution");
  lcd.setCursor(2,1);
  lcd.print("Monitoring System");
  lcd.setCursor(0,2);
  lcd.print("Frankfurt University");
  lcd.setCursor(2,3);
  lcd.print("Applied Sciences");

  delay(3000);
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("High Integrity");
  lcd.setCursor(6,2);
  lcd.print("Systems");
  delay(3000);
  lcd.clear();


}
