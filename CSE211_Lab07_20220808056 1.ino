#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

#define BUTTON 2
#define DHTP 7
#define DHT_TYPE    DHT11

DHT_Unified dht(DHTP, DHT_TYPE);
LiquidCrystal lcd(13,12,11,10,9,8);

volatile bool state = false;
sensors_event_t event;

void setup() {
  dht.begin();
  lcd.begin(16,2);
  lcd.print("Temp & Humidity Monitor");
  lcd.setCursor(0,1);
  lcd.print("Irem KARAKAPLAN");
  delay(2000);
  lcd.clear();
  pinMode(BUTTON, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON), switchState, RISING);
}

void loop() {
  if (state){
  temperature();
  }   
  else if(!state) humidity();
}

void switchState() {
  state = !state;
}

void temperature() {
  lcd.setCursor(0,0);
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    lcd.print(F("Error reading temperature!"));
  }
  else {
    lcd.print(F("Temperature     "));
    lcd.setCursor(0,1);
    lcd.print(event.temperature);
    lcd.print(F("°C              "));
  }
}

void humidity() {
  lcd.setCursor(0,0);
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    lcd.print(F("Error reading humidity!"));
  }
  else {
    lcd.print(F("Humidity        "));
    lcd.setCursor(0,1);
    lcd.print(event.relative_humidity);
    lcd.print(F("%               "));
  }
}
