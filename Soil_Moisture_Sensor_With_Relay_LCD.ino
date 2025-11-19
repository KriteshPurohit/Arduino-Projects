#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("IRRIGATION");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM IS ON");
    lcd.print("");
    delay(3000);
  lcd.clear();
}
 
void loop() {
  int value = analogRead(A0);
  Serial.println(value);
  
  if (value > 950) {
    lcd.setCursor(0, 0);
    lcd.print("LandSlide Risk High");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("LandSlide Chances Low");
  }
 
  if (value < 300) {
    lcd.setCursor(0, 1);
    lcd.print("Moisture:HIGH");
    {digitalWrite(12, HIGH);
    delay(500);
    digitalWrite(12, LOW);}
    {digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);}
  } else if (value > 300 && value < 950) {
    lcd.setCursor(0, 1);
    lcd.print("Moisture:MID ");
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  } else if (value > 950) {
    lcd.setCursor(0, 1);
    lcd.print("Moisture:LOW ");
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
}
