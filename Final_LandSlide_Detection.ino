//accelerometer ka SDA arduino ke SDA me or SCL arduino ke SCL me. VCC ko 5V arduino or GND ko GND arduino me.
//Buzzer ki lambi side(positive side) pin no.12 me or LED ki lambi side pin no.13 me.dusri sides ko GND arduino me.
//Soil Moisture ke A0 ko arduino A0 se or VCC ko 5V arduino and GND ko GND arduino se.
//I2C Display ke SDA ko A4 arduino se or SCL ko A5 arduino se, VCC ko VCC arduino and GND ko GND arduino se.

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int ADXL345 = 0x53;
int Xout, Yout, Zout;
int X_out, Y_out, Z_out;
int Xval, Yval, Zval;
int minval = -20, maxval = 20;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(ADXL345);
  Wire.write(0x2D); //talk to POWER_CTL Register - 0x2D
  Wire.write(8); // Bit D3 High for measuring enable (8dec -> 0000 1000 binary)
  Wire.endTransmission();

  Wire.beginTransmission(ADXL345);
  Wire.write(0x32);
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true);
  Xout = ( Wire.read() | Wire.read() << 8);
  Yout = ( Wire.read() | Wire.read() << 8);
  Zout = ( Wire.read() | Wire.read() << 8);
  Wire.endTransmission();
   
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("LandSlide Detection");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM IS ON");
    lcd.print("");
    delay(3000);
  lcd.clear();
}
 
void loop() {
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32);
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true);
  X_out = ( Wire.read() | Wire.read() << 8);
  Y_out = ( Wire.read() | Wire.read() << 8);
  Z_out = ( Wire.read() | Wire.read() << 8);
 
 Xval = Xout - X_out;
 Yval = Yout - Y_out;
 Zval = Zout - Z_out;
 {Serial.print(Xval);
  Serial.print(" ");
  Serial.print(Yval);
  Serial.print(" ");
  Serial.println(Zval);
  delay(100);
 }
 
  if (minval > Xval || Xval > maxval || minval > Yval || Yval > maxval || minval > Zval || Zval > maxval) {
    lcd.setCursor(0, 0);
    lcd.print("High Risk LandSlide");
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Low Risk LandSlide");
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
  
  int value = analogRead(A0);
  Serial.println(value);
 
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
