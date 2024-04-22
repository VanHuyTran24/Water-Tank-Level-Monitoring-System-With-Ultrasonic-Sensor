#include <DHT.h> // Thu vien cam bien DHT
#include <OneWire.h> // Thu vien giao tiep 1 chan
#include <DallasTemperature.h> // Thu vien cam bien Da18B20
#include <EEPROM.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>  // Thu vien man LCD

#define pumpSwitch 2
#define modeSwitch 3
#define ONE_WIRE_BUS 4
#define DHTPin 6
#define DHTType DHT11
#define trigPin 8
#define echoPin 9
#define relay 12

int percentage;
bool pump; 
float speedOfSound, distance, exactDistance, level, set_val, duration, tempC_DHT, hum, tempC_DS, xxx1, xxx2;

DHT dht(DHTPin,DHTType);
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  lcd.begin(20, 4);
  lcd.backlight();
  lcd.setCursor(4, 0); 
  lcd.print("WATER LEVEL:");
  lcd.setCursor(0, 2);
  lcd.print("PUMP: ");
  lcd.setCursor(9, 2);
  lcd.print("MODE: ");
  lcd.setCursor(0, 3);
  lcd.print("TEMPERATURE:");
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pumpSwitch, INPUT_PULLUP); // Dien tro keo len de khong bi "tha noi"
  pinMode(modeSwitch, INPUT_PULLUP); // Dien tro keo len de khong bi "tha noi"
  pinMode(relay, OUTPUT);

  set_val = EEPROM.read(0); // Doc du lieu tu vi tri 0

  dht.begin();
  sensors.begin();
  Serial.begin(9600); // Mo cong giao tiep voi Laptop
}
void loop() {
  digitalWrite(trigPin, HIGH); // Phat xung
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); // Thu xung
  duration = pulseIn(echoPin, HIGH); // Khoang thoi gian song am truyen di va phan xa lai

  tempC_DHT = dht.readTemperature();
  hum = dht.readHumidity();
  speedOfSound = getspeedOfSound(tempC_DHT, hum);
  distance = getDistance(duration, speedOfSound);
  exactDistance = kalmanFilter(distance);
  level = set_val - exactDistance;   
  percentage = level*100/set_val;

  sensors.requestTemperatures(); // Doc nhiet do
  tempC_DS = sensors.getTempCByIndex(0); // Hien thi nhiet do cua cam bien o vi tri 0

  if(digitalRead(pumpSwitch)==LOW && digitalRead(modeSwitch)==HIGH) {
    set_val = exactDistance;
    EEPROM.write(0, set_val); // Set do cao cua binh chua vao vi tri 0
    } 
  if(digitalRead(pumpSwitch)==LOW && digitalRead(modeSwitch)==LOW) pump = 1;
  if(digitalRead(pumpSwitch)==HIGH && digitalRead(modeSwitch)==LOW) pump = 0;  

  lcd.setCursor(4, 1);
  if (level < 0) level = 0;
  lcd.print(level, 1);
  lcd.print("CM   ");
    
  lcd.setCursor(13, 1); 
  if(percentage < 0) percentage = 0;
  lcd.print(percentage);
  lcd.print("%  ");

  if(percentage < 20 && digitalRead(modeSwitch) == HIGH) pump = 1;
  if(percentage > 75) pump = 0;
  digitalWrite(relay, !pump);
     
  lcd.setCursor(5, 2);
  if(pump == 1) lcd.print("ON ");
  else if(pump == 0) lcd.print("OFF");
   
  lcd.setCursor(14,2);
  if(digitalRead(modeSwitch) == LOW) lcd.print("MANUAL");
  else lcd.print("AUTO  ");

  lcd.setCursor(12, 3);
  lcd.print(tempC_DS, 1);
  lcd.write(0xdf);
  lcd.print("C  ");
}
float getspeedOfSound(float tempC_DHT, float hum) {
  speedOfSound = 331.4 + (0.6 * tempC_DHT) + (0.0124 * hum); // Tinh toc do cua am thanh m/s
  return speedOfSound;
}
float getDistance(float duration, float speedOfSound) {
  duration = duration/1000000; // Doi micro giay sang giay
  distance = speedOfSound * (duration/2);
  distance = distance * 100; // Doi m sang cm
  if (distance >= 0) { // Loc nhieu
    xxx1 = distance;
    delay(300);
  }
  if (distance >= 0) {
    xxx2 = distance;
  }
  if (isnan(distance) && xxx2 - xxx1 > 0) xxx2 = xxx1;
  return xxx2;
}
float kalmanFilter(float U) {
  static const float R = 0.2; // Noise measurement convariance
  static const float H = 1.00;
  static const float Q = 5; // Noise system convariance
  static float P = 0;
  static float P = 0;
  static float U_hat = 0;
  static float K = 0;
  K = P*H/(H*P*H+R);
  U_hat = U_hat + K*(U-H*U_hat);
  P = (1-K*H)*P+Q;
  return U_hat;
}